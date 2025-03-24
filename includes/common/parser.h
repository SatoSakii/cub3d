/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:43:49 by albernar          #+#    #+#             */
/*   Updated: 2025/03/18 18:51:30 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define ERR_MSG	"Not enough arguments\0Too many arguments\0No file type\0\
Invalid extension type\0Invalid file\0Permission denied\0\
No such file or directory\0Duplicate textures found\0\
Duplicate colors found\0Invalid texture path\0\
Invalid color\0Invalid line\0Missing infos\0Invalid tile\0Too much player\0\
Missing player\0Error while allocating memory\0"
# define PROCESS_ERR		-1
# define PROCESS_OK			0
# define PROCESS_SKIP_LINE	2
# define DEFAULT_MALLOC_SIZE 8

typedef enum e_error
{
	NO_ERR = -1,
	ERR_NOT_ENOUGH_ARGS = 0,
	ERR_TOO_MANY_ARGS = ERR_NOT_ENOUGH_ARGS + sizeof("Not enough arguments"),
	ERR_NO_FILE_TYPE = ERR_TOO_MANY_ARGS + sizeof("Too many arguments"),
	ERR_INVALID_EXTENSION = ERR_NO_FILE_TYPE + sizeof("No file type"),
	ERR_INVALID_FILE = ERR_INVALID_EXTENSION + sizeof("Invalid extension type"),
	ERR_PERMISSION_DENIED = ERR_INVALID_FILE + sizeof("Invalid file"),
	ERR_NO_FILE_FOUND = ERR_PERMISSION_DENIED + sizeof("Permission denied"),
	ERR_DUPLICATE_TEXTURE = (ERR_NO_FILE_FOUND
			+ sizeof("No such file or directory")),
	ERR_DUPLICATE_COLOR = (ERR_DUPLICATE_TEXTURE
			+ sizeof("Duplicate textures found")),
	ERR_INVALID_TEXTURE = (ERR_DUPLICATE_COLOR
			+ sizeof("Duplicate colors found")),
	ERR_INVALID_COLOR = ERR_INVALID_TEXTURE + sizeof("Invalid texture path"),
	ERR_INVALID_LINE = ERR_INVALID_COLOR + sizeof("Invalid color"),
	ERR_MISSING_INFO = ERR_INVALID_LINE + sizeof("Invalid line"),
	ERR_INVALID_TILE = ERR_MISSING_INFO + sizeof("Missing infos"),
	ERR_TOO_MUCH_PLY = ERR_INVALID_TILE + sizeof("Invalid tile"),
	ERR_NO_PLY = ERR_TOO_MUCH_PLY + sizeof("Too much player"),
	ERR_MALLOC = ERR_NO_PLY + sizeof("Missing player"),
}	t_error;

typedef struct s_error_ctx
{
	char	**args;
	char	*executable;
	char	*filename;
	char	*line_content;
	int		error_pos;
	int		error_len;
	int		line_num;
}	t_error_ctx;

typedef struct s_game	t_game;

// Args
int		validate_argument_count(int argc, char **argv, t_error_ctx *ctx);
int		validate_file_extension(t_error_ctx *ctx);
int		validate_open_file(t_error_ctx *ctx);

// Elements
int		parse_data(int fd, t_error_ctx *ctx);
int		handle_texture(char *line, t_error_ctx *ctx);
int		handle_color(char *l, t_error_ctx *ctx);

// Error
void	throw_err(t_error error, t_error_ctx *ctx);
void	apply_ctx(t_error_ctx *ctx, int error_len, int error_pos);

// Utils
void	skip_spaces(char **line);
int		check_line_validity(t_error_ctx *ctx, char *line, int *found);
int		info_hasspace(char **line, t_error_ctx *ctx, t_event *event);

// Map
void	fill_map(int fd, t_error_ctx *ctx, t_game *game);
int		check_map_validity(t_game *game, t_error_ctx *ctx);
int		parse_map(int fd, t_error_ctx *ctx, t_game *game);

#endif