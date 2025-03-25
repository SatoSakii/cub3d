/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 02:47:39 by albernar          #+#    #+#             */
/*   Updated: 2025/03/25 02:59:10 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	imgui_color_additional(ImGuiStyle *style)
{
	style->Colors[ImGuiCol_TitleBgCollapsed] = (ImVec4){0.259f, 0.259f,
		0.259f, 0.0f};
	style->Colors[ImGuiCol_MenuBarBg] = (ImVec4){0.0f, 0.0f, 0.0f, 0.0f};
	style->Colors[ImGuiCol_ScrollbarBg] = (ImVec4){0.157f, 0.157f, 0.157f, .0f};
	style->Colors[ImGuiCol_ScrollbarGrab] = (ImVec4){0.157f, 0.157f,
		0.157f, 1.0f};
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = (ImVec4){0.235f, 0.235f,
		0.235f, 1.0f};
	style->Colors[ImGuiCol_ScrollbarGrabActive] = (ImVec4){0.294f, 0.294f,
		0.294f, 1.0f};
	style->Colors[ImGuiCol_CheckMark] = (ImVec4){0.502f, 0.302f, 1.0f, 0.549f};
	style->Colors[ImGuiCol_SliderGrab] = (ImVec4){0.502f, 0.302f,
		1.0f, 0.549f};
	style->Colors[ImGuiCol_SliderGrabActive] = (ImVec4){0.502f, 0.302f,
		1.0f, 0.549f};
	style->Colors[ImGuiCol_Button] = (ImVec4){0.502f, 0.302f, 1.0f, 0.549f};
	style->Colors[ImGuiCol_ButtonHovered] = (ImVec4){0.502f, 0.302f,
		1.0f, 0.549f};
	style->Colors[ImGuiCol_ButtonActive] = (ImVec4){0.5f, 0.3f, 1.0f, 0.549f};
	style->Colors[ImGuiCol_Tab] = (ImVec4){0.502f, 0.302f, 1.0f, 0.549f};
	style->Colors[ImGuiCol_TabHovered] = (ImVec4){0.502f, 0.302f, 1.0f, 0.549f};
	style->Colors[ImGuiCol_PlotLines] = (ImVec4){0.294f, 0.294f, 0.294f, 1.0f};
	style->Colors[ImGuiCol_PlotLinesHovered] = (ImVec4){0.502f, 0.302f,
		1.0f, 0.549f};
	style->Colors[ImGuiCol_Text] = (ImVec4){1.0f, 1.0f, 1.0f, 1.0f};
}

void	setup_imgui_colors(ImGuiStyle *style)
{
	style->Colors[ImGuiCol_TextDisabled] = (ImVec4){1.0f, 1.0f,
		1.0f, 0.3605149984359741f};
	style->Colors[ImGuiCol_WindowBg] = (ImVec4){0.098f, 0.098f, 0.098f, 1.0f};
	style->Colors[ImGuiCol_ChildBg] = (ImVec4){1.0f, 0.0f, 0.0f, 0.0f};
	style->Colors[ImGuiCol_PopupBg] = (ImVec4){0.098f, 0.098f, 0.098f, 1.0f};
	style->Colors[ImGuiCol_Border] = (ImVec4){0.502f, 0.302f, 1.0f, 0.549f};
	style->Colors[ImGuiCol_BorderShadow] = (ImVec4){0.0f, 0.0f, 0.0f, 0.0f};
	style->Colors[ImGuiCol_FrameBg] = (ImVec4){0.157f, 0.157f, 0.157f, 1.0f};
	style->Colors[ImGuiCol_TextSelectedBg] = (ImVec4){0.502f, 0.302f,
		1.0f, 0.549f};
	style->Colors[ImGuiCol_DragDropTarget] = (ImVec4){1.0f, 1.0f, 0.0f, 0.9f};
	style->Colors[ImGuiCol_NavWindowingHighlight] = (ImVec4){1.0f, 1.0f,
		1.0f, 0.7f};
	style->Colors[ImGuiCol_NavWindowingDimBg] = (ImVec4){0.8f, 0.8f,
		0.8f, 0.2f};
	style->Colors[ImGuiCol_ModalWindowDimBg] = (ImVec4){0.8f, 0.8f,
		0.8f, 0.35f};
	style->Colors[ImGuiCol_FrameBgHovered] = (ImVec4){0.380f, 0.423f,
		0.572f, 0.549f};
	style->Colors[ImGuiCol_FrameBgActive] = (ImVec4){0.502f, 0.302f,
		1.0f, 0.549f};
	style->Colors[ImGuiCol_TitleBg] = (ImVec4){0.098f, 0.098f, 0.098f, 1.0f};
	style->Colors[ImGuiCol_TitleBgActive] = (ImVec4){0.098f, 0.098f,
		0.098f, 1.0f};
	imgui_color_additional(style);
}
