/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eeravci <eeravci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:28:42 by eeravci           #+#    #+#             */
/*   Updated: 2025/06/26 20:19:18 by eeravci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *strjoin_three_and_free(char *s1, char *s2, char *s3)
{
    char *res;
    char *temp;

    temp = ft_strjoin(s1, s2);
    if(!temp)
        return NULL;
    res = ft_strjoin(temp, s3);
    if(!res)
        return NULL;
    free(res);
    return (res);
}

void    free_array(char **arr)
{
    int i;
    
    if(!arr)
        return ;
    i = 0;
    while(arr[i])
        free(arr[i++]);
    free(arr);
}
