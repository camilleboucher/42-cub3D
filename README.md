_This project has been created as part of the 42 curriculum by cboucher and yben-dje._

# cub3D

## Description

Cub3D is the final C project in 42’s common core. Developed in pair, it challenges us to build a basic raycaster inspired by Wolfenstein 3D (1992). The project involves parsing the map and asset information, including wall textures and floor and ceiling colors. For the bonus features, we added doors that open and close, a minimap, mouse support, and some animations.

### Bonus++

To make the game even more fun, we added a menu, split-screen multiplayer for up to four players, controller support, 2D sprites (billboards) and a hidden Easter egg 👀!

### Technical details and design choices

Cub3D uses a raycasting engine to create a 3D-like view of a 2D map. For each vertical screen column, the program casts a ray from the player’s position and calculates where it first hits a wall. The distance to that wall determines its height on the screen. The DDA (Digital Differential Analyzer) algorithm efficiently traces each ray through the map grid, stepping from one cell boundary to the next until it finds a wall. This approach provides fast rendering while keeping the world represented as a simple 2D grid.

## Instructions

### Compilation

Clone with
```bash
git clone --recursive https://github.com/camilleboucher/42-cub3D.git
```

Use `make bonus`, `make` or `make re` to compile the program. For cleaning the generated files use `make clean` or `make fclean`.
We recommend using the bonus program to access all the features.

### Usage

To use the cub3D program, run cub3D with a .cub map file.

Example for the bonus program : `./cub3D_bonus maps/valid/bonus/ultimate_demo_bonus.cub`

Move the player with the `W`, `A`, `S`, and `D` keys. Press `F` to open doors and `LEFT SHIFT` to run.
With a controller you can open doors with `X` (`Square`) or `RIGHT STICK` and you can run with `LEFT SHOULDER` or `RIGHT SHOULDER`.

## Resources

1.	MacroLibX Documentation : [https://macrolibx.kbz8.me/]
2.	Raycasting : [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
3.	[DDA (Digital Differential Analyzer)](https://www.youtube.com/watch?v=NbSee-XM7WA)
4.	Wikipedia Article: [Fonction trigonométrique](https://fr.wikipedia.org/wiki/Fonction_trigonom%C3%A9trique)
5.	Web research and AI chat for documentation. No IA was used to write code.

### Player sprites

1.	[Mao Mao](https://greatcharacters.miraheze.org/wiki/File:Maomao_Anime_Design_Season_2.png)
2.	[Jinshi](https://greatcharacters.miraheze.org/wiki/File:Jinshi_anime_season_2.png)
3.	[Xiaolan](https://www.animecharactersdatabase.com/characters.php?id=133148)
4.	[Gaoshun](https://www.animecharactersdatabase.com/characters.php?id=133147)
