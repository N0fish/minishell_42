/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:53:48 by alex              #+#    #+#             */
/*   Updated: 2024/08/04 14:51:43 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void execute_simple_command(cmd_node* node, bool stdin_pipe, bool stdout_pipe, int pipe_read, int pipe_write, char *redirect_in, char *redirect_out)
{
    cmd_internal cmd;
    init_command_internal(node, &cmd, stdin_pipe, stdout_pipe, pipe_read, pipe_write, redirect_in, redirect_out);
	execute_command_internal(&cmd);
	destroy_command_internal(&cmd);
}

static void execute_redirections(cmd_node* node, bool stdin_pipe, bool stdout_pipe, int pipe_read, int pipe_write)
{
    cmd_node    *cmd = node;
    cmd_node    *cmd2;
    char    *res;
    if (node == NULL)
        return;
    //work with many redirections isn't finished
    printf("start\n");
    while (cmd && cmd->type == NODE_REDIRECT_OUT)
    {
        
        res = malloc(sizeof(char*) * (5));
        strcpy(res, "ls");
        printf("res: %s\n", res);
        cmd2 = malloc(sizeof(cmd_node));
        cmd2->data = res;
        cmd2->type = NODE_CMDPATH;
        printf("node->right->data: %s and node->data: %s\n", cmd2->data, cmd->data);
        execute_simple_command(cmd2, stdin_pipe, stdout_pipe, pipe_read, pipe_write, NULL, cmd->data);
        cmd = cmd->right;
    }
}

static void execute_command(cmd_node* node, bool stdin_pipe, bool stdout_pipe, int pipe_read, int pipe_write)
{
    if (node == NULL)
        return;
    if (node->type == NODE_REDIRECT_OUT)
        execute_redirections(node, stdin_pipe, stdout_pipe, pipe_read, pipe_write);
        //execute_simple_command(node->right, stdin_pipe, stdout_pipe, pipe_read, pipe_write, NULL, node->data);
	else if (node->type == NODE_CMDPATH)
		execute_simple_command(node, stdin_pipe, stdout_pipe, pipe_read, pipe_write, NULL, NULL);
}

static void execute_pipeline(cmd_node* tree)
{
    int file_desc[2];
	int p_write;
	int p_read;

	pipe(file_desc);
	p_write = file_desc[1];
    p_read = file_desc[0];
    execute_command(tree->left, false, true, 0, p_write);
    cmd_node* job = tree->right;
    while (job != NULL && job->type == NODE_PIPE)
    {
        close(p_write);
        pipe(file_desc);
        p_write = file_desc[1];
        execute_command(job->left, true, true, p_read, p_write);
        close(p_read);
        p_read = file_desc[0];
        job = job->right;
    }
    p_read = file_desc[0];
    close(p_write);
    execute_command(job, true, false, p_read, 0);
    close(p_read);
}

void executor(cmd_node* node)
{
	if (node == NULL)
        return ;
	if (node->type == NODE_PIPE)
		execute_pipeline(node);
	else
		execute_command(node, false, false, 0, 0);
}
