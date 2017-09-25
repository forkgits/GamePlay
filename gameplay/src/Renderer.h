#pragma once

#include "Component.h"
#include "Graphics.h"
#include "Mesh.h"
#include "Material.h"

namespace gameplay
{

/**
 * Defines a base component that makes objects visible.
 *
 * All renderers have a mesh which can have one or more parts.
 * All renderers have either a shared material or a material per/part.
 * All subclasses control the loading of assets, creation
 * of mesh and materials and the rendering through Graphics.
 */
class Renderer : public Component
{
public:

	friend class Graphics;
	friend class SceneObject;

	/**
	 * Defines the draw flags for rendering.
	 */
	enum DrawFlags
	{
		DRAW_FLAGS_SOLID,
		DRAW_FLAGS_WIREFRAME,
		DRAW_FLAGS_DEBUG
	};

	/**
	 * Constructor.
	 */
    Renderer();
    
	/**
	 * Destructor.
	 */
    ~Renderer();

	/**
	 * Gets the url this renderer was loaded from if loaded from an asset.
	 *
	 * @return The url this renderer was loaded from if loaded from an asset.
	 */
	std::string getUrl() const;

    /**
     * Gets the Mesh for this Renderer.
     *
     * @return The Mesh for this Renderer.
     */
	std::shared_ptr<Mesh> getMesh() const;

    /**
     * Sets the Mesh for this Renderer.
     *
     * @return The Mesh for this Renderer.
     */
	void setMesh(std::shared_ptr<Mesh> mesh);

    /**
     * Gets the number of parts in the Mesh for this Model.
     *
     * @return The number of parts in the Mesh for this Model.
     */
    size_t getMeshPartCount() const;

    /**
     * Gets the Material bound to the specified mesh part.
     *
     * If partIndex is >= 0 and no Material is directly bound to the specified
     * mesh part, the shared Material will be returned.
     *
     * @param partIndex The index of the mesh part whose Material to return (-1 for shared material).
     *
     * @return The requested Material, or nullptr if no Material is set.
     */
	std::shared_ptr<Material> getMaterial(int partIndex = -1);

    /**
     * Sets a material to be used for drawing this Model.
     *
     * The specified Material is applied for the part at the given index in
     * this Model's Mesh. A partIndex of -1 sets a shared Material for
     * all mesh parts, whereas a value of 0 or greater sets the Material for the
     * specified mesh part only.
     *
     * Mesh parts will use an explicitly set part material, if set; otherwise they
     * will use the globally set material.
     *
     * @param material The new material.
     * @param partIndex The index of the mesh part to set the material for (-1 for shared material).
     */
	void setMaterial(std::shared_ptr<Material> material, int partIndex = -1);

    /**
     * Determines if a (non-shared) material is set for the specified part index.
     *
     * @param partIndex MeshPart index.
     *
     * @return true if a material is set for the specified part, false otherwise.
     */
    bool hasMaterial(size_t partIndex) const;

    /**
     * @see Serializable::onDeserialize
     */
	virtual void onSerialize(Serializer* serializer);

    /**
     * @see Serializable::onDeserialize
     */
    virtual void onDeserialize(Serializer* serializer);

	/**
	 * Determines if all the renderer's resource are loaded.
	 *
	 * @return true if all the renderer's resource are loaded, false if not loaded.
	 */
	bool isLoaded() const;

protected:

	/**
	 * Event occurs when renderer's resource are loaded
	 *
	 * @param drawFlags The flags indicating what is rendered.
	 */
	virtual void onLoaded();

	/**
	 * Event occurs when the scene requests for renderer to be drawn.
	 *
	 * @param drawFlags The flags indicating what is rendered.
	 */
	virtual void onDraw(unsigned int drawFlags) = 0;

	std::string  _url;
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Material> _materialShared;
	std::vector<std::shared_ptr<Material>> _materials;
	int _partCount;
	bool _loaded;
};

}