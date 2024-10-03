// Змінні для зберігання шейдерів
VkPipeline closeLODShader;
VkPipeline midLODShader;
VkPipeline farLODShader;
VkPipeline currentPipeline; // Curent graphic pipeline

// Функція для вибору шейдера на основі фактора LOD
void selectShaderBasedOnLOD()
{
    if (shaderConstants.FacNew == 1.0f)
        currentPipeline = closeLODShader;
    else if (shaderConstants.FacNew == 0.5f)
        currentPipeline = midLODShader;
    else
        currentPipeline = farLODShader;
}

// Виклик у renderLoop
void renderLoop()
{
    while (true)
    {
        float distance = calculateDistanceToCamera();

        auto currentTime = std::chrono::steady_clock::now();
        float timeSinceLastUpdate = std::chrono::duration<float>(currentTime - lastUpdateTime).count();
        if (timeSinceLastUpdate > updateInterval)
        {
            updateShaderConstantsBasedOnDistance(distance);
            selectShaderBasedOnLOD(); // Update shader
        }

        updateInterpolation();

        // Використовуйте currentPipeline для рендеру кадра
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, currentPipeline);
        drawFrame();
    }
}
