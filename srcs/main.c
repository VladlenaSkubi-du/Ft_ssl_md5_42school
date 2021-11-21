/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:14:29 by sschmele          #+#    #+#             */
/*   Updated: 2021/11/21 17:29:59 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256_notmine.h"

int				ssl_main_start(char *algo_name, t_celldata *cmd_data)
{
	int			answer;

	answer = cmd_data->start_algo_function(0);
	if (answer)
	{
		if (answer == -1)
			ssl_errors_management(ERR_ALGO_NOTFOUND, algo_name, 0, 0);
		else if (answer == 1)
			ssl_errors_management(ERR_ALGO, NULL, 0, 0);
		return (1);
	}
	return (0);
}

static int		ssl_prepare_main_environment(void)
{
	ssl_save_available_commands();
	ssl_init_data_buffer();
	return (0);
}

/*
** For debugging:
** print_options(*flags);
** in the end before return (0);
*/

static size_t	ssl_main_actions_with_possible_errors(int argc, char **argv,
					char *algo_name, int *flags)
{
	t_celldata	*cmd_data;
	size_t		answer;

	answer = ssl_check_command(algo_name);
	if (answer == SIZET_MAX)
		return (SIZET_MAX);
	cmd_data = ssl_get_data_from_hashtable(answer);
	if (cmd_data == NULL)
		return (SIZET_MAX);
	answer = ssl_parse_arguments(argc - 1, argv + 1, flags, cmd_data->flags);
	if (answer == SIZET_MAX)
		return (SIZET_MAX);
	ssl_init_output_buffer();
	answer = ssl_main_start(algo_name, cmd_data);
	if (answer)
		return (SIZET_MAX);
	return (0);
}

static int		ssl_clean_main_environment(void)
{
	ssl_free_data_buffer();
	ssl_clean_saved_commands();
	ssl_free_output_buffer();
	return (0);
}

/*
** g_sslcmd_list_start_func[answer_cmd] is the main function call
*/

int				main(int argc, char **argv)
{
	size_t		answer;
	char		*algo_name;
	int			flags;

	if (argc < 2 || !argv[1])
	{
		ssl_usage();
		return (1);
	}
	algo_name = argv[1];
	flags = 0;
	ssl_prepare_main_environment();
	answer = ssl_main_actions_with_possible_errors(argc, argv,
		algo_name, &flags);
	if (answer == SIZET_MAX)
		return (1);
	ssl_output(algo_name, flags);
	ssl_clean_main_environment();
 	//////////////////////////////////////////
	// printf("other algo:\n");
	// BYTE text1[] = {"abc"};  
	// BYTE hash1[SHA256_BLOCK_SIZE] = {0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
	// //         0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad};        
	// BYTE text1[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
	// BYTE hash1[SHA256_BLOCK_SIZE] = {0x24,0x8d,0x6a,0x61,0xd2,0x06,0x38,0xb8,0xe5,0xc0,0x26,0x93,0x0c,0x3e,0x60,0x39,
	//                                  0xa3,0x3c,0xe4,0x59,0x64,0xff,0x21,0x67,0xf6,0xec,0xed,0xd4,0x19,0xdb,0x06,0xc1};
	// BYTE text1[] = {"hello world"}; 
	// BYTE hash1[SHA256_BLOCK_SIZE] = {0xb9,0x4d,0x27,0xb9,0x93,0x4d,0x3e,0x08,0xa5,0x2e,0x52,0xd7,0xda,0x7d,0xab,0xfa,
	//                                  0xc4,0x84,0xef,0xe3,0x7a,0x53,0x80,0xee,0x90,0x88,0xf7,0xac,0xe2,0xef,0xcd,0xe9};
	// BYTE text1[] = {"abcde"}; 
	// BYTE hash1[SHA256_BLOCK_SIZE] = {0x36, 0xbb, 0xe5, 0x0e, 0xd9, 0x68, 0x41, 0xd1, 0x04, 0x43, 0xbc, 0xb6, 0x70, 0xd6, 0x55, 0x4f, 
	// 								0x0a, 0x34, 0xb7, 0x61, 0xbe, 0x67, 0xec, 0x9c, 0x4a, 0x8a, 0xd2, 0xc0, 0xc4, 0x4c, 0xa4, 0x2c};
	// BYTE text1[] = {"# Ft_ssl_md5_42school. The aim is to recode part of the OpenSSL program, specifically the MD5 and SHA-256 hashing algorithms."}; 
	// BYTE hash1[SHA256_BLOCK_SIZE] = {0xe3, 0xb7, 0xe3, 0x81, 0x11, 0x55, 0x35, 0x34, 0x9b, 0x6e, 0xb7, 0xb3, 0x6d, 0xd8, 0xe5, 0x24, 
	// 									0x96, 0xfe, 0xff, 0xf6, 0x54, 0x7c, 0x94, 0x72, 0xc5, 0x31, 0x37, 0x1c, 0x3e, 0xbd, 0xda, 0x53};
	// SHA256_CTX ctx;
	// BYTE buf[SHA256_BLOCK_SIZE];
	// int pass = 1;
	// sha256_init(&ctx);
	// sha256_update(&ctx, text1, strlen(text1));
	// sha256_final(&ctx, buf);
	// pass = pass && !memcmp(hash1, buf, SHA256_BLOCK_SIZE);
	// printf("SHA-256 tests: %s\n", pass ? "SUCCEEDED" : "FAILED");
	//////////////////////////////////////
	return (0);
}
