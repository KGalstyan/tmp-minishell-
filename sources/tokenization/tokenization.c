/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:31:25 by vkostand          #+#    #+#             */
/*   Updated: 2024/09/26 19:55:42 by kgalstya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_tokens(t_data *data)
{
    data->i = 0;
    data->j = 0;
    data->quotes_flag = NONE;
    while(data->input[data->i])
    {
        data->j = data->i;
        if(check_pipe_red_env(data))
            continue;
        else if(check_quotes(data))
            continue;
        else if(check_space(data))
            continue;
        while(data->input[data->i] && data->input[data->i] != ' ')
        {   
            if(data->input[data->i] == '<' || data->input[data->i] == '>')
                break;
            else if(data->input[data->i] == '$' || data->input[data->i] == '|')
                break;
            else if(data->input[data->i] == '"' || data->input[data->i] == '\'')
                break;
            data->i++;
        }
        fill_tokens(data, data->i, data->j, data->quotes_flag);
    }
}

void print_datas(t_data *data)
{
    t_token *pr_token = data->tokens;
    while(pr_token != NULL)
    {
        printf("original token is -->    |%s|\n", pr_token->original_content);
        printf("status is-->      %d\n\n", pr_token->quotes);
        //printf("type is ------------>>     %d\n", pr_token->type);
        printf("⚪️⚪️⚪️⚪️⚪️⚪️⚪️⚪️⚪️\n");
        pr_token = pr_token->next;
    }
}

void error_exit(t_data *data)
{
    printf("⛔️ INCORRECT INPUT\n");
    free_data(data);
    system("leaks minishell");
    exit(4);
}

void tokenization(t_data *data)
{
    create_tokens(data);
    allot_quotes_value(data);
    tokens_insertion(data);
}
void start_shell(t_data *data)
{
    while(1)
    {
        data->input = readline("Verishen: ");
        tokenization(data);
        print_datas(data);
        printf("✅ CORRECT INPUT\n");
        free_data(data);
        system("leaks minishell");
    }
}