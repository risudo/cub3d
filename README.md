# cub3d
![norminette](https://github.com/risudo/cub3d/workflows/norminette/badge.svg)
<img alt="GitHub" src="https://img.shields.io/github/license/risudo/cub3d">

Rendering a 3D game using ray-casting.

## Demo

https://user-images.githubusercontent.com/76856052/154199872-6d689496-71b8-4795-8169-9ffc503fa201.mov

## Usage

### build

```
$ make
```
### launch

```
./cub3D "cubfile"
```
Argument: the path to cubfile that has infomation of game.

#### example

```
$ ./cub3D cubfiles/example.cub
```

### test
```
$ make test && cat log.txt
```

## Requirement

I have tested it on Ubuntu and Mac.

On Mac, Xquarts needs to be installed.

# For more info

rsudo's Hatena Blog: [3Dゲームを作る課題の振り返り](https://rio-1.hatenablog.com/entry/2022/02/16/114122?_ga=2.250761679.871799974.1644805093-702415775.1516097932)
