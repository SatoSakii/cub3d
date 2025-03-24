/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:00:53 by albernar          #+#    #+#             */
/*   Updated: 2025/03/19 21:19:34 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

typedef enum e_controls_state
{
	RELEASE,
	DOWN,
	WAITING_FOR_INPUT
}	t_controls_state;

typedef struct s_keybinds
{
	int					keycode;
	t_controls_state	state;
}	t_keybinds;

typedef struct s_clickbinds
{
	/* CLICK BUTTON */
	t_controls_state	state;
}	t_clickbinds;

/*
	FEATURES REQUEST: PLACE WALL AT CURSOR POS WITH DDA ALGORITHM
	CURRENTLY, ONLY UNDO THE LAST WALL DESTROYED
*/

typedef struct s_controls
{
	t_keybinds			keys[8];
	t_clickbinds		clicks[1];
}	t_controls;

#endif