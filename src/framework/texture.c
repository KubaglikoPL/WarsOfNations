#include <framework/texture.h>
#include <stb_rect_pack.h>
#include <stb_image.h>
#include <malloc.h>
#include <string.h>

fwTexture_t loadTexture(Renderer renderer, textureLoadInfo_t* loadInfos, uint32_t loadInfosAmount, uint32_t size) {
	fwTexture_t t;
	t.w = size;
	t.h = size;
	stbrp_rect* rects = alloca(sizeof(stbrp_rect) * loadInfosAmount);
	memset(rects, 0, sizeof(stbrp_rect) * loadInfosAmount);

	stbrp_context ctx;
	stbrp_node* nodes = alloca(sizeof(stbrp_node) * size);
	memset(nodes, 0, sizeof(stbrp_node) * size);
	stbrp_init_target(&ctx, 512, 512, nodes, size);

	for (uint32_t i = 0; i < loadInfosAmount; i++) {
		textureLoadInfo_t* loadInfo = &loadInfos[i];
		int x, y, comp;
		stbi_info(loadInfo->filepath, &x, &y, &comp);
		rects[i].w = x;
		rects[i].was_packed = false;
		rects[i].h = y;
		rects[i].id = 0;
		rects[i].x = 0;
		rects[i].y = 0;
	}
	stbrp_pack_rects(&ctx, rects, loadInfosAmount);

	t.texture = createTexture(renderer, size, size);
	t.subTextures = malloc(sizeof(subTexture_t) * loadInfosAmount);
	t.num_subTextures = loadInfosAmount;
	for (uint32_t i = 0; i < loadInfosAmount; i++) {
		textureLoadInfo_t* loadInfo = &loadInfos[i];
		int x, y, comp;
		void* data = stbi_load(loadInfo->filepath, &x, &y, &comp, 4);
		stbrp_rect *rect = &rects[i];
		updateTexture(renderer, t.texture, rect->x, rect->y, rect->w, rect->h, data);
		stbi_image_free(data);

		subTexture_t* sub = &t.subTextures[i];
		sub->ID = loadInfo->ID;
		sub->x = rect->x;
		sub->y = rect->y;
		sub->w = rect->w;
		sub->h = rect->h;
		sub->xf = rect->x / (float)size;
		sub->yf = rect->y / (float)size;
		sub->wf = rect->w / (float)size;
		sub->hf = rect->h / (float)size;
	}
	return t;
}

fwTexture_t loadSingleTexture(Renderer renderer, const char* filepath) {
	int x, y, comp;
	void* data = stbi_load(filepath, &x, &y, &comp, 4);
	fwTexture_t t;
	t.texture = createTexture(renderer, x, y);
	updateTexture(renderer, t.texture, 0, 0, x, y, data);
	t.w = x;
	t.h = y;
	t.num_subTextures = 0;
	t.subTextures = NULL;
	stbi_image_free(data);
	return t;
}
