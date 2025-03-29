/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:20:36 by albernar          #+#    #+#             */
/*   Updated: 2025/03/29 01:36:37 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_direction
{
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT
}	t_direction;

typedef enum e_rotation
{
	ROTATION_LEFT,
	ROTATION_RIGHT
}	t_rotation;

typedef enum e_walldir
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_walldir;

typedef enum e_main_menu
{
	START_MENU,
	MAIN_MENU,
	SETTINGS_MENU,
	CONTROLS_MENU,
	IN_GAME
}	t_main_menu;

#endif