# CGT 215 Lab 06 - Simple Image Compositing

This project combines a background image with a green-screen foreground image. Green or transparent foreground pixels are replaced with the background pixel at the same `(x, y)` coordinate.

## Build

Open `CGT215_Lab6.vcxproj` in Visual Studio, install the `SFML_VS2019` NuGet package, and run the project from the project directory so the relative `images1/...` paths resolve.

## Default assets

- Background: `images1/backgrounds/winter.png`
- Foreground: `images1/characters/yoda.png`
