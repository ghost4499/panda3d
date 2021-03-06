/**
 * PANDA 3D SOFTWARE
 * Copyright (c) Carnegie Mellon University.  All rights reserved.
 *
 * All use of this software is subject to the terms of the revised BSD
 * license.  You should have received a copy of this license along
 * with this source code in a file named "LICENSE."
 *
 * @file vulkanVertexBufferContext.I
 * @author rdb
 * @date 2016-02-18
 */

/**
 *
 */
INLINE VulkanVertexBufferContext::
VulkanVertexBufferContext(PreparedGraphicsObjects *pgo,
                          GeomVertexArrayData *data) :
  VertexBufferContext(pgo, data),
  _buffer(VK_NULL_HANDLE) {
}
