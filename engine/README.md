# Lys Engine

## Architecture

### Render Hardware Interface

The following diagram shows the implementation of the Render Hardware Interface (RHI).
The RHI declares generic types with behavior that is implemented by each platform implementation.
Each platform implementation implements the logic described by the RHI and manages GPU resources.

Any platform-specific features shall be exposed in only its low-level GPU interface.

```mermaid
graph TB
    App["Application Layer"]
    
    subgraph RHI["Render Hardware Interface (RHI)"]
        RHITypes["RHI Modules"]
        subgraph Platform["Platform Implementations"]
            Metal["Metal<br/>(macOS)"]
            Vulkan["Vulkan<br/>(Cross-Platform)"]
        end
    end
    
    subgraph GPU["GPU APIs"]
        MetalAPI["Metal API"]
        VulkanAPI["Vulkan API"]
    end
    
    subgraph Resources["GPU Resources"]
        Resources_A["RHI Types"]
        Resources_B["RHI Classes"]
    end
    
    App -->|Uses| RHI
    RHITypes -->|Defines| Resources
    Metal -->|Uses| MetalAPI
    Vulkan -->|Uses| VulkanAPI
    MetalAPI -->|Implements| Resources
    VulkanAPI -->|Implements| Resources
    
    style App fill:#1976d2,stroke:#0d47a1,stroke-width:2px,color:#000000
    style RHI fill:#e1f5ff,stroke:#0277bd,stroke-width:2px,color:#000000
    style RHITypes fill:#b3e5fc,stroke:#0277bd,stroke-width:2px,color:#000000
    style Platform fill:#b3e5fc,stroke:#0277bd,stroke-width:2px,color:#000000
    style Metal fill:#81d4fa,stroke:#0277bd,stroke-width:2px,color:#000000
    style Vulkan fill:#81d4fa,stroke:#0277bd,stroke-width:2px,color:#000000
    style GPU fill:#fff3e0,stroke:#f57c00,stroke-width:2px,color:#000000
    style MetalAPI fill:#ffe0b2,stroke:#f57c00,stroke-width:2px,color:#000000
    style VulkanAPI fill:#ffe0b2,stroke:#f57c00,stroke-width:2px,color:#000000
    style Resources fill:#f3e5f5,stroke:#6a1b9a,stroke-width:2px,color:#000000
    style Resources_A fill:#e1bee7,stroke:#6a1b9a,stroke-width:2px,color:#000000
    style Resources_B fill:#e1bee7,stroke:#6a1b9a,stroke-width:2px,color:#000000
```
