/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 02:45:14 by albernar          #+#    #+#             */
/*   Updated: 2025/03/27 21:59:53 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	imgui_style_additional(ImGuiStyle *style)
{
	style->WindowMinSize = (ImVec2){30.0f, 30.0f};
	style->WindowTitleAlign = (ImVec2){0.5f, 0.5f};
	style->WindowMenuButtonPosition = ImGuiDir_Right;
	style->ChildRounding = 5.0f;
	style->ChildBorderSize = 1.0f;
	style->PopupRounding = 10.0f;
	style->PopupBorderSize = 0.0f;
	style->FramePadding = (ImVec2){5.0f, 3.5f};
	style->FrameRounding = 5.0f;
	style->FrameBorderSize = 0.0f;
	style->ItemSpacing = (ImVec2){5.0f, 4.0f};
	style->ItemInnerSpacing = (ImVec2){5.0f, 5.0f};
	style->CellPadding = (ImVec2){4.0f, 2.0f};
	style->IndentSpacing = 5.0f;
	style->ColumnsMinSpacing = 5.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 15.0f;
	style->GrabRounding = 5.0f;
	style->TabRounding = 5.0f;
	style->TabBorderSize = 0.0f;
	style->ColorButtonPosition = ImGuiDir_Right;
	style->ButtonTextAlign = (ImVec2){0.5f, 0.5f};
	style->SelectableTextAlign = (ImVec2){0.0f, 0.0f};
}

void	setup_imgui_style(void)
{
	ImGuiStyle	*style;

	style = igGetStyle();
	style->Alpha = 1.0f;
	style->DisabledAlpha = 0.1000000014901161f;
	style->WindowPadding = (ImVec2){8.0f, 8.0f};
	style->WindowBorderSize = 0.0f;
	imgui_style_additional(style);
	setup_imgui_colors(style);
}
