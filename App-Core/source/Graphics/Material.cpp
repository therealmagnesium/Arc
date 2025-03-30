#include "Graphics/Material.h"

namespace Arc
{
    namespace Graphics
    {
        static Material defaultMaterial;

        Material& GetDefaultMaterial()
        {
            return defaultMaterial;
        }

    }
}
