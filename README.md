# BabySense

**BabySense** is an embedded prototype baby monitor designed to assist both parents and babies. It was created during the **Neapolis Innovation Summer Campus 2024 (NISC)**, a week-long hackathon hosted at **STMicroelectronics Naples**.

The project was built from scratch in under 5 days, combining sensor data, real-time alerts, and playful interaction in a dual-device system.

> 📁 Original codebase was hosted on a TortoiseSVN instance provided by STMicroelectronics.

## 👶 Concept

BabySense consists of two parts:

- **Parent Unit**: Displays environmental data (e.g. temperature, noise), and triggers an alarm if a customizable decibel threshold is exceeded.
- **Baby Unit**: Engages the child through mini-games (Rock Paper Scissors, Animal and Shape Recognition), and responds to touch to simulate basic emotional feedback.

🎥 [Watch a short demo on YouTube](https://youtu.be/uJ5wRD_ZAyA)

## 📸 Photos

<table>

<tr>
<td><img src="readme_assets/1.jpeg" width="500"/></td>
<td><img src="readme_assets/2.jpeg" width="500"/></td>
</tr>

<tr>
<td>BabySense Units</td>
<td></td>
</tr>

<td><img src="readme_assets/3.jpeg" width="500"/></td>
<td><img src="readme_assets/4.png" width="500"/></td>

<tr>
<td>Display testing</td>
<td>Close up on parent unit</td>
</tr>

</table>

## 🔧 Technologies & Hardware

The project was created in about a week using a **STM NucleoG4 board**. We used the **ChibiStudio** toolchain that included an IDE and ChibiOS, a free embedded real time operating system.

We employed many sensors provided by the hackathon:

| Component | Purpose |
|----------|---------|
| **IR Sensor** | Communication between baby and parent units |
| **Temperature & Humidity Sensor** | Environmental monitoring |
| **Proximity Sensor** | Petting detection on baby unit |
| **Microphone** | Sound input for alarm threshold |
| **Buttons** | Input for interaction and configuration |
| **Four 48x84 LCDs** | UI display on both devices |
| **Speaker** | Alarm sound feedback |

The outer casing was made with recycled materials (cardboard, tape, markers), with a playful design on the baby unit and a minimal interface for the parent side.

## 👥 Team

Developed by an interdisciplinary team of students during NISC 2024:

| Name | Course |
|------|--------|
| Luigi Inquieto | Computer Engineering |
| Fabrizio Bonomo | Computer Engineering |
| Lorenzo Cavaliere | Computer Engineering |
| Teresa Di Dona | Computer Engineering |
| Manuel Loffredo | Computer Engineering |
| Carmine Sorrentino | Computer Engineering |
| Simone Boscaglia | Computer Science |
| Luca Criscuolo | Cybersecurity |

<td><img src="readme_assets/team.jpg" width="500"/></td>


## 🛠️ Status

This is a **functional prototype** developed in under a week. Further iterations would involve:

- Power optimization
- Expanded gameplay logic and UI polish
- Data logging for long-term monitoring

## 📫 Contact

This repository is maintained as a reference for the hackathon outcome. For inquiries, feel free to open an issue or reach out directly.
