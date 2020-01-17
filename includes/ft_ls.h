/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:58:40 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/17 05:29:35 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libftprintf/includes/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>

# define MAX_PATH 1024
# define SEMI_YEAR 60 * 60 * 24 * 365 / 2
# define FULL_EXIT 1

typedef struct	s_options
{
	int		list;
	int		recursive;
	int		all;
	int		reverse;
	int		time_order;
	/*
	**	служебные переменные
	*/	
	char	illegal;
	char	**files_array;
	char	**dir_array;
	int		len_for_array[2];
	int		flag;
	int		list_files;
	int		flag_spec;
	char	cur_dir[MAX_PATH];
	int		tab_len[7];
	int		count;
	int		bug_ls_for_recursion;
}				t_options;

typedef struct	s_info
{
	char		*name;
	char		mode[12];
	char		type;
	char		*user;
	char		*group;
	int			nlink;
	intmax_t	size;
	int			major_num;
	int			minor_num;
	char		*time_create;
	long		time_create_digit;
	char		*time_modif;
	long		time_modif_digit;
	char		*time_active;
	long		time_active_digit;
	intmax_t	total;
	intmax_t	total_no_all;
	char		*path_link;
	int			flag_link;
	int			full_params;
}				t_info;

/*
**	main.c
*/
int		error_message(char *str, int exit_flag);

/*
**	options.c
*/
void	init_options(t_options *options, int ac);
int		input_options(t_options *options, char *params);

/*
**	ft_ls.c
*/
int		final_ls(t_options *options);
int		ft_ls(t_options *options);

int	processing_dir(t_options *options, t_info *list, char *file);
int	processing_files(t_options *options, t_info *list);
int	processing(t_options *options, char *file);

/*
**	reader.c
*/
int		reading(t_info *list, char *file, t_options *options);
int		reading_one_file(t_info *list, char name[1024], t_options *options, int i);

/*
**	printer.c
*/
int		printing(t_info *list, t_options *options, int len);
void	print_list(t_info *list, int i, t_options *options);

/*
**	lib_ls.c
*/
void	sort_ascii(char **array, int num);
t_info	*set_info_list(int len);
void	set_null_tab_len(t_options *options);
void	update_value_tab_len(t_options *options, t_info *list, int len);
void	sort_info_list(t_info *list, int len, t_options *options);
void	set_path(t_options *options, char *file);
int		update_path(t_options *options, char *path);
intmax_t	total_counter(t_info *list, int len, int all);
int		add_path(char *directory, char *path);
int		delete_last_path(char *directory);

/*
**	option_R.c
*/
int		recursive(t_options *options, char *file);

/*
**	option_l.c
*/
int		get_list_params(char *file, t_info *list, int i);

#endif