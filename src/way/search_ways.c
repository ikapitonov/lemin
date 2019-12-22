/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_ways.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 21:13:58 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/15 21:13:59 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

static	t_node	*get_node(t_node *start)
{
	t_link	*tmp;

	tmp = start->linkbox->link;
	while (tmp)
	{
		if (tmp->is_true == 1)
		{
			tmp->is_true = -1;
			tmp->coming = 1;
			return (tmp->node);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static	int		counter(t_main *main)
{
	t_node	*tmp;
	int		count;

	count = 1;
	tmp = main->waybox->start;
	if (!(tmp = get_node(tmp)))
		return (0);
	while ((tmp = get_node(tmp)))
		++count;
	return (count);
}

static	t_way	*get_struct(t_node **here)
{
	t_node	*node;
	t_link	*link;
	t_way	*new;

	node = *here;
	link = node->linkbox->link;
	while (link)
	{
		if (link->coming)
		{
			link->coming = 0;
			*here = link->node;
			if (!(new = (t_way*)malloc(sizeof(t_way))))
				die();
			new->name = link->node->name;
			new->ant = 0;
			return (new);
		}
		link = link->next;
	}
	return (NULL);
}

static	int		fnorm(t_way ***way, t_main *main)
{
	t_node	*tmp;
	int		final;
	int		count;
	int		i;
	int		j;

	j = 0;
	final = 0;
	while ((count = counter(main)))
	{
		if (!(way[j] = (t_way**)malloc((1 + count) * sizeof(void*))))
			die();
		i = 0;
		final = count > final ? count : final;
		tmp = main->waybox->start;
		while (i < count)
			way[j][i++] = get_struct(&tmp);
		way[j][i] = NULL;
		++j;
	}
	way[j] = NULL;
	set_result(way, j, final, main);
	return (j);
}

int				search_ways(t_main *main, t_graph *graph)
{
	t_way	***way;
	int		ways_len;

	if (!(ways_len = ways_count(main, graph)))
		return (0);
	if (!(way = (t_way***)malloc((1 + ways_len) * sizeof(void*))))
		die();
	return (fnorm(way, main));
}
