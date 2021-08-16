/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:03:59 by a18979859         #+#    #+#             */
/*   Updated: 2021/08/16 19:22:17 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash_usage.h"

int	work_with_add_hash(char *line, int i, int word_beg)
{
	char	*new_key;
	void	*cell_data;
	size_t	answer_from_btin;

	new_key = ft_strndup(line + word_beg, new_norm(line, i, word_beg));
	if (new_key[0] != 0)
	{
		if (ft_strlen(new_key) >= KEY_LENGTH)
			return (error_management(&new_key, KEY_TOO_LONG, 1));
		cell_data = init_hashdata();
		if (cell_data == NULL)
			return (error_management(&new_key, PROGRAMM_ERROR, 0));
		fill_hashdata(&cell_data, new_key, 1);
		answer_from_btin = btin_hash_valid_argument_add(new_key, cell_data);
		if (answer_from_btin == ADD_CELLEXISTS)
		{
			clean_hashdata(cell_data);
			free(cell_data);
			return (error_management(&new_key, ADD_CELLEXISTS, 1));
		}
		if (answer_from_btin == SIZET_MAX)
			return (error_management(&new_key, PROGRAMM_ERROR, 0));
	}
	free(new_key);
	return (0);
}

int	work_with_delete_hash(char *line, int i, int word_beg)
{
	char	*new_key;
	size_t	answer_from_btin;

	if (line[word_beg] == '-')
		return (0);
	new_key = ft_strndup(line + word_beg, new_norm(line, i, word_beg));
	if (new_key[0] != 0)
	{
		if (ft_strlen(new_key) >= KEY_LENGTH)
			return (error_management(&new_key, KEY_TOO_LONG, 1));
		answer_from_btin = btin_hash_valid_argument_delete(new_key);
		if (answer_from_btin == SIZET_MAX)
			return (error_management(&new_key, PROGRAMM_ERROR, 0));
		else if (answer_from_btin == FIND_NOKEY)
			return (error_management(&new_key, FIND_NOKEY, 1));
		else if (answer_from_btin == DELETE_HASHTABLE_EMPTY)
			return (error_management(&new_key, DELETE_HASHTABLE_EMPTY, 0));
	}
	free(new_key);
	return (0);
}

int	work_with_find_hash(char *line, int i, int word_beg)
{
	char	*new_key;
	size_t	answer_from_btin;

	if (line[word_beg] == '-')
		return (0);
	new_key = ft_strndup(line + word_beg, new_norm(line, i, word_beg));
	if (new_key[0] != 0)
	{
		if (ft_strlen(new_key) >= KEY_LENGTH)
			return (error_management(&new_key, KEY_TOO_LONG, 1));
		answer_from_btin = btin_hash_valid_argument_find(new_key);
		if (answer_from_btin == SIZET_MAX)
			return (error_management(&new_key, PROGRAMM_ERROR, 0));
		else if (answer_from_btin == FIND_NOKEY)
			return (error_management(&new_key, FIND_NOKEY, 1));
		else if (answer_from_btin == DELETE_HASHTABLE_EMPTY)
			return (error_management(&new_key, DELETE_HASHTABLE_EMPTY, 0));
	}
	free(new_key);
	return (0);
}

int	work_with_clean_hash(void)
{
	size_t	answer_from_btin;

	answer_from_btin = btin_hash_clean_hashtable();
	if (answer_from_btin == SIZET_MAX)
		return (error_management(NULL, PROGRAMM_ERROR, 0));
	else if (answer_from_btin == DELETE_HASHTABLE_EMPTY)
		return (error_management(NULL, DELETE_HASHTABLE_EMPTY, 0));
	return (0);
}

int	work_with_list_hash(void)
{
	size_t	answer_from_btin;

	answer_from_btin = btin_hash_list_hashtable();
	if (answer_from_btin == SIZET_MAX)
		return (error_management(NULL, PROGRAMM_ERROR, 0));
	else if (answer_from_btin == DELETE_HASHTABLE_EMPTY)
		return (error_management(NULL, DELETE_HASHTABLE_EMPTY, 0));
	return (0);
}
