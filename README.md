# Corne Keymap

> The Corne keyboard is a split keyboard with 3x6 column staggered keys and 3 thumb keys, based on Helix. Crkbd stands for Corne Keyboard.
> [Foostan](https://github.com/foostan/crkbd)

## Intro

![crkbd picture](https://i.imgur.com/0a4Ofn3.jpg)
*[Deskmat is called Mizu Deskmat: Water]*

This keyboard was bought from [Little Keyboards](https://www.littlekeyboards.com/collections/corne-pcb-kits/products/corne-mx-hotswap-pcb-kit-v3) with an assembly service included since I did not have the tools nor the confidence to solder the board flawlessly 💸💸.

A summary of features that have been changed:

| General detail               | Description                                                       |
|------------------------------|-------------------------------------------------------------------|
| Layers are kept the same way | `QWERTY`, `LOWER`, `RAISE` and `ADJUST`                           |
| OLED print orientation       | `270deg` -- facing the user (I don't want to twist my head 🙃 )   |
| Customized `glcdfont`        | Logos and indicators have been removed and replaced.              |

This personalized keymap is based on my [Ergodox EZ layout](https://configure.ergodox-ez.com/ergodox-ez/layouts/GZO3M/latest/0) which uses the thumb keys for multiple actions. For example, typing on the spacebar will return a `space` character but holding it will make it act as a `CTRL` key.

## Features

These are the Features that are needed for the keyboard:

| Feature                                                                                                           | Description                   |
|-------------------------------------------------------------------------------------------------------------------|-------------------------------|
| [EXTRAKEY_ENABLE](https://beta.docs.qmk.fm/faqs/faq_misc#special-extra-key-doesnt-work-system-audio-control-keys) | For Audio control             |
| [WPM_ENABLE](https://beta.docs.qmk.fm/using-qmk/software-features/feature_wpm)                                    | Words Per Minute calculations |
| [RGB_MATRIX_ENABLE](https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_rgb_matrix)             | RGB LEDs                      |

## Specs

This keymap has been developed for a Corne keyboard containing:

| Component          | Quantity |
|--------------------|----------|
| Elite-C v4         | 2        |
| 128x32 OLED Screen | 2        |

Here are the full details of the keyboard (if you are interested):

| Components    | Details                                |
|---------------|----------------------------------------|
| PCB           | Corne Choc Hotswap - Black             |
| Case          | Corne Technician Key - Transparent     |
| Switches      | Kailh Choc Brown                       |
| Keycaps       | Transparent                            |

## OLED

### Master side

![master oled](https://i.imgur.com/WDDMG4v.jpg)

The master OLED displays:

* the active layer;
* the matrix coordinates and keycode;
* LED Indicators (only `Num Lock` and `Caps Lock`);
* WPM counter;
* WPM graph.

### Slave side

![slave oled](https://i.imgur.com/urKvP9i.jpg)

The slave OLED displays:

* the Corne logo;
* HSV values;
* and my favorite mascot.

## glcdfont

The `glcdfont` has been modified to display [Kapibara-san](https://anime-kapibarasan.com/), a Japanese cartoon character representing a capybara with a moving animation based on WPM.

![animation](https://i.imgur.com/dqvNCL3.gif)

To edit the `glcdfont`, I recommend using the [QMK Logo Editor](https://joric.github.io/qle/) by [joric](https://github.com/joric/qle) which helps a lot.

![glcdfont](https://i.imgur.com/aTFxHzS.png)

## How to run

### Default keymap

This is for a regular (standard) / home / everyday keymap layout:

```bash
# Left side
make crkbd:lazyproof:dfu-split-left

# Right side
make crkbd:lazyproof:dfu-split-right
```

### Code keymap

For coding on an OSX environment with shortcuts meant for web debugging:

```bash
make crkbd:lazyproof:dfu-split-<left|right> TEMPLATE=code
```

### Discord

For a one-sided keyboard that acts as an emoji dashboard (more will be explained in the `Templating` section):

```bash
make crkbd:lazyproof:dfu-split-right TEMPLATE=discord SIDE=right
```

## Templating

This is a proof of concept that uses the 2 microcontrollers to their full extent.

* Each microcontroller will have the same configuration for:
  * layers;
  * OLED display;
  * and RGB config.
* Only the keymapping would change based on the arguments written on the console.

### Example: Left CODE and Right DISCORD

Plugging the left side keyboard and running:

```bash
make crkbd:lazyproof:dfu-split-left TEMPLATE=code
```

Then plugging the right side:

```bash
make crkbd:lazyproof:dfu-split-left TEMPLATE=discord SIDE=right
```

From there, plugging the keyboard on the left side would mean using the `default` template **for the entire keyboard**.

To go straight to the `discord` macros, plug on the right side of the keyboard.

### Pros

* More customization possibilities for one-handed keyboards or simple keymaps.
* The lazy hardware version of `TO(layer)` (direct switch to a layer).
* More keymaps can be added if the OLED and RGB configuration for each layer remains the same.
* Easier to experiment with new keymapping by using one side of the keyboard: one side for the original, the other side for a lab experiment. No need to stash changes, recompile the correct version, or switch branching.

### Cons

* Cannot have a different OLED or RGB config otherwise the keyboard will have layer behavior discrepancy: each has their brain and won't display their lights / OLED normally.
* Could add more layers but doesn't scale well: adding a new layer would possibly mean editing all the templates (UNLESS there's an RGB and OLED configuration for each template).
* Not futureproof: it's a hassle to maintain and to remember which template is used on which keyboard side.

## Credits

| Name                                                                                                                 | Remarks                                                                                                            |
|----------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------|
| [foostan](https://github.com/foostan/crkbd)                                                                          | For making the keyboard                                                                                            |
| drashna                                                                                                              | All his contribution and improvement for crkbd                                                                     |
| [brickbots](https://www.reddit.com/r/MechanicalKeyboards/comments/evimyg/kyria_is_kool_onboard_wpm_calc_oled_graph/) | Sharing the WPM graph code for the Kyria keyboard                                                                  |
| [joric](https://github.com/joric/qle)                                                                                | For the `glcdfont` editor and having the import / export image feature                                             |
| [j-inc](https://www.reddit.com/r/olkb/comments/h00a8b/i_made_an_oled_animation_of_bongo_cat_that/)                   | The Bongo Cat animation which I tried to implement but didn't have enough storage. Still took inspiration from it! |
