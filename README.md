_This project has been created as part of the 42 curriculum by cboucher and yben-dje._

# cub3D

## Description

WORK IN PROGRESS

## Instructions

### Compilation

Use `make` or `make re` to compile the program. For cleaning the generated files use `make clean` or `make fclean`.

### Usage

To use the cub3D program, run cub3D with a .cub map file.

Example : `./cub3D maps/1.cub`

## Resources

1.	MacroLibX Documentation : [https://macrolibx.kbz8.me/]
2.	[Key codes](https://wiki.libsdl.org/SDL2/SDL_Scancode)
3.	Raycasting : [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
4.	[DDA (Digital Differential Analyzer)](https://www.youtube.com/watch?v=NbSee-XM7WA)
5.	Wikipedia Article: [Fonction trigonométrique](https://fr.wikipedia.org/wiki/Fonction_trigonom%C3%A9trique)
3.	Web research and AI chat for some notions about double linked list.

TODO :
1 ) PARSING:tester toutes les erreurs de parsing pottentiels :
	A ) si la ligne se fini il faut quand meme continuer jusqua map->width pour voir si 0 au dessus de rien (check map invalid/			dup_player_AND_open_map.cub par exemple)
2 ) changer map statique en dynamique

PRISE DE NOTE :
view vector : (cos angle, sin angle) -> direction du rayon de la vue
distance rayon (theoreme de pythagore) : hypotenuse = sqrt(dx^2 + dy^2)
pente(slope or gradient) : m =
