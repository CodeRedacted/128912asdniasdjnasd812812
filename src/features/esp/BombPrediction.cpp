#pragma once

namespace bomb_prediction 
{
    inline void draw_impact_x(const vec2_t& screen_pos, ImU32 color, float size = 10.0f, float thickness = 1.0f) 
    {
        // Line 1: Top-Left to Bottom-Right
        g_render->line(
            screen_pos.x - size, screen_pos.y - size, 
            screen_pos.x + size, screen_pos.y + size, 
            color, thickness
        );

        // Line 2: Top-Right to Bottom-Left
        g_render->line(
            screen_pos.x + size, screen_pos.y - size, 
            screen_pos.x - size, screen_pos.y + size, 
            color, thickness
        );
    }

    inline void run() 
    {
        // Safety checks for local player and state
        if (!sdk::cLocalPlayer || !sdk::cGame || !sdk::cGame->ballistics)
            return;

        if (sdk::cLocalPlayer->getGuiState() != GuiState::ALIVE && sdk::cLocalPlayer->getGuiState() != GuiState::SPEC)
            return;

        // Check if the player is in a plane to enable bomb logic
        if (sdk::cLocalPlayer->getLocalUnit().getInfo().isPlane()) 
        {
            const auto camera_matrix = sdk::cGame->camera->getCameraMatrix();
            vec3_t bombImpact = sdk::cGame->ballistics->getBombImpactPoint();

            vec2_t screen_position;
            if (g_render->world_to_screen(bombImpact, screen_position, camera_matrix)) 
            {
                // Draw the original circle
                g_render->circle(screen_position.x, screen_position.y, 6.0f, IM_COL32(255, 0, 200, 255), 16.0f);

                // Draw the requested "X" at the impact point
                // Using a bright neon color for visibility
                draw_impact_x(screen_position, IM_COL32(255, 255, 255, 255), 8.0f, 1.5f);
            }
        }
    }
}