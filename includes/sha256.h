/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:38:59 by a18979859         #+#    #+#             */
/*   Updated: 2021/11/06 17:34:43 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H
# define FT_SHA256_H

/*
** File sha256_start.c
*/

int		sha256_algorithm_start(size_t data_size);

/*
** File sha256_output_hash.c
*/

int		sha256_output_hash(void);

# endif