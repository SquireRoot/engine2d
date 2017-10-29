#pragma once

namespace engine2d {
	struct Component {
		Entity* attatchedEntity;
		GUID id;

		Component(Entity* entity) {
			attatchedEntity = entity;
			CoCreateGuid(&id);
		}
	};
}