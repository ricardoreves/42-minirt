/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:31:39 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/18 03:54:20 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
#include "minirt.h"
void free_array(char *arr[]);
void print_array(char *arr[]);
int array_length(char *arr[]);
float	str_to_float(char *str);

// A   0.2             255,255,255

// int is_dis_char()
//  {
//      char *charset = "ACLsplcy0123456789-,. ";

//     while (str && str[++i])
//     {
//         if (str[] == )
//     }
//}

char *sanitize_line(char *line)
{
    int i;
    char *tmp;

    i = -1;
    tmp = line;
    while (tmp && tmp[++i])
        if (tmp[i] == '\t' || tmp[i] == '\n')
            tmp[i] = ' ';
    line = ft_strtrim(tmp, " ");
    free(tmp);
    return (line);
}

void parse_ambient_line(char *line, t_rt *rt)
{
    char **arr;

    arr = ft_split(line, ' ');
    if (array_length(arr) != 3)
    {
        ft_putendl_fd("Error: too few ambient arguments", 2);
        exit(1);
    }
    print_array(arr);
    free_array(arr);
}

int parse_line(char *line, t_rt *rt)
{
    if (ft_strncmp(line, "A", 1) == 0)
        parse_ambient_line(line, rt);
    // if (ft_strncmp(line, "C", 1) == 0)
    //     parse_ambiant();
    // if (ft_strncmp(line, "L", 1) == 0)
    //     parse_ambiant();
    // if (ft_strncmp(line, "sp", 2) == 0)
    //     parse_ambiant();
    // if (ft_strncmp(line, "pl", 2) == 0)
    //     parse_ambiant();
    // if (ft_strncmp(line, "cy", 2) == 0)
    //     parse_ambiant();
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    int i;
    int fd;
    char *line;
    char *filename = "../scenes/mandatory.rt";
    t_rt *rt;

    i = -1;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error");
        exit(1);
    }
    rt = ft_calloc(sizeof(t_rt), 1);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        line = sanitize_line(line);
        parse_line(line, rt);
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    free(rt);

    // printf("%f %f\n", 0.0245000, str_to_float("0.0245000"));
    // printf("%f %f\n", 1.000846, str_to_float("1.000846"));
    // printf("%f %f\n", 10.011000, str_to_float("10.011000"));
    // printf("%f %f\n", 100.011280, str_to_float("100.011280"));
    // printf("%f %f\n", -0.466130, str_to_float("-0.466130"));    
    // printf("%f %f\n", -2.000846, str_to_float("-2.000846"));    
    // printf("%f %f\n", -20.011000, str_to_float("-20.011000"));
    return (0);
}