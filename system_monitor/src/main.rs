use sysinfo::{System, Disks, Networks, Components, Cpu};
use std::thread;
use std::time::Duration;
use plotters::prelude::*;
use plotters::style::colors::*;

const HISTORY_LENGTH: usize = 100;

fn draw_cpu_usage_chart(history: &[f32]) {
    let root_area = BitMapBackend::new("cpu_usage.png", (640, 480)).into_drawing_area();
    root_area.fill(&WHITE).unwrap();
    
    let mut chart = ChartBuilder::on(&root_area)
        .caption("CPU Usage", ("sans-serif", 50))
        .margin(10)
        .set_label_area_size(LabelAreaPosition::Left, 40)
        .set_label_area_size(LabelAreaPosition::Bottom, 40)
        .build_cartesian_2d(0..HISTORY_LENGTH as i32, 0f32..100f32)
        .unwrap();
    
    chart.configure_mesh().draw().unwrap();
    
    chart.draw_series(LineSeries::new(
        history.iter().enumerate().map(|(i, &v)| (i as i32, v)),
        &RED,
    )).unwrap();
}

fn main() {
    let mut sys = System::new_all();
    let mut cpu_usage_history = vec![0.0; HISTORY_LENGTH];
    
    loop {
        sys.refresh_all();
        
        println!("\nSystem Monitor");
        println!("----------------");
        
        let cpu_usage = sys.cpus().iter().map(|cpu| cpu.cpu_usage()).sum::<f32>() / sys.cpus().len() as f32;
        println!("CPU Usage: {:.2}%", cpu_usage);
        
        cpu_usage_history.remove(0);
        cpu_usage_history.push(cpu_usage);
        draw_cpu_usage_chart(&cpu_usage_history);
        
        println!("Total Memory: {} MB", sys.total_memory() / 1024);
        println!("Used Memory: {} MB", sys.used_memory() / 1024);
        println!("Processes: {}", sys.processes().len());
        
        let disks = Disks::new_with_refreshed_list();
        for disk in &disks {
            println!("Disk: {:?}, Available: {} MB", disk.name(), disk.available_space() / 1024 / 1024);
        }
        
        let components = Components::new_with_refreshed_list();
        for component in &components {
            println!("{} Temperature: {:.1}°C", component.label(), component.temperature());
        }
        
        thread::sleep(Duration::from_secs(2));
    }
}
