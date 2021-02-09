# Corne Keymap

> The Corne keyboard is a split keyboard with 3x6 column staggered keys and 3 thumb keys, based on Helix. Crkbd stands for Corne Keyboard.
> [Foostan](https://github.com/foostan/crkbd)

## Intro

![crkbd picture](https://i.imgur.com/0a4Ofn3.jpg)
*[Deskmat is called Mizu Deskmat: Water]*

Ordered in September 2020 and received a month later, this keyboard was bought from [Little Keyboards](https://www.littlekeyboards.com/collections/corne-pcb-kits/products/corne-mx-hotswap-pcb-kit-v3) with assembly service included since I did not have the tools nor the confidence to solder the board flawlessly 💸💸.

A short summary of the details that have been changed:

| General detail               | Description                                                       |
|------------------------------|-------------------------------------------------------------------|
| Layers are kept the same way | `QWERTY`, `LOWER`, `RAISE` and `ADJUST`                           |
| OLED print orientation       | `270deg` -- facing the user (I don't wanna twist my head 🙃 )     |
| Customized `glcdfont`        | Logos and indicators have been removed and replaced. |

## Specs

This keymap has been developed for a Corne keyboard containing:

| Component          | Quantity |
|--------------------|----------|
| Elite-C v4         | 2        |
| 128x32 OLED Screen | 2        |

If you'd like to know the complete details of the keyboard:

| Components    | Details                                |
|---------------|----------------------------------------|
| PCB           | Corne Choc Hotswap - Black             |
| Case          | Corne Technician Key - Transparent     |
| Switches      | Kailh Choc Brown                       |
| Keycaps       | Transparent                            |
| TRRS [Angled] | [Mechcables](https://mechcables.com/)  |
| USB Cable     | [Mechcables](https://mechcables.com/)  |
The cables are black paracord, transparent techflex and transparent heatshrink.

## OLED

### Master side

![master oled](https://i.imgur.com/WDDMG4v.jpg)

The master OLED displays:

* the active layer;
* the matrix coordinates and keycode;
* LED Indicators (`Num Lock` and `Caps Lock` only);
* WPM counter;
* WPM graph.

### Slave side

![slave oled](https://i.imgur.com/urKvP9i.jpg)

The slave OLED displays:

* the Corne logo;
* HSV values;
* and my favorite mascot with walking animation based on WPM.

## glcdfont

The `glcdfont` has been modified to include [Kapibara-san](https://anime-kapibarasan.com/), a japanese cartoon character representing a capybara.

![glcdfont](https://i.imgur.com/aTFxHzS.png)

To edit the `glcdfont`, using [QMK Logo Editor](https://joric.github.io/qle/) helps.

## Templating

WIP

## How to run

### Default keymap

This is for a normal / home / everyday keymap layout:

```bash
# Left side
make crkbd:lazyproof:dfu-split-left

# Right side
make crkbd:lazyproof:dfu-split-right
```

### Code keymap

For coding on an OSX environment with shortcuts meant for web debugging: 

```bash
make crkbd:lazyproof:dfu-split-left|right TEMPLATE=code
```

### Discord

For a one-sided keyboard that acts as an emoji dashboard:

```bash
make crkbd:lazyproof:dfu-split-right TEMPLATE=discord SIDE=right
```
