/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 19:38:03 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/09 19:15:08 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	processing_files(t_options *options, t_info *list)
{
	struct stat	about;
	struct stat	about_link;
	int			count;
	char		*file;

	count = 0;
	while (count < options->len_for_array[0])
	{
		file = options->files_array[count];
		if (stat(file, &about))
			error_message("processing_files stat");
		lstat(file, &about_link);
		if (S_ISLNK(about_link.st_mode))
		{
			list[count].flag_link = 1;
			set_path(options, file);
			if (reading_one_file(list, file, options, count))
				return (-1);
		}
		else
		{
			set_path(options, "./\0");
			list[count].name = options->files_array[count];
			if (reading_one_file(list, file, options, count))
				return (-1);
		}
		count++;
		options->flag_list = 1;
	}
	return (count);
}
