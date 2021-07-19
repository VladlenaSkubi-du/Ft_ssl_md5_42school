/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:40:12 by sschmele          #+#    #+#             */
/*   Updated: 2021/07/19 22:54:02 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_FUNCTIONS_H
# define PRINT_FUNCTIONS_H

void		print_options(int flags);
void        print_bits(char *str);
void		print_bits_as_32uint_little_endian(uint32_t number);
void		print_bits_as_32uint_big_endian(uint32_t number);

#endif