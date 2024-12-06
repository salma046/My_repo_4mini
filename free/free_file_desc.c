/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file_desc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 05:44:05 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/04 05:44:10 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_files(int **files)
{
    int i = 0;

    if (!files)
        return;
    while (files[i])
    {
        free(files[i]);
        i++;
    }
    free(files); // Free the outer array
}


