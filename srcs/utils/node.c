#include "minishell.h"

bool	is_redirect_node(cmd_node *node)
{
	return (node->type == NODE_REDIRECT_IN\
		|| node->type == NODE_REDIRECT_OUT);
}
