/**
 * PANDA 3D SOFTWARE
 * Copyright (c) Carnegie Mellon University.  All rights reserved.
 *
 * All use of this software is subject to the terms of the revised BSD
 * license.  You should have received a copy of this license along
 * with this source code in a file named "LICENSE."
 *
 * @file vulkanGraphicsWindow.h
 * @author rdb
 * @date 2016-02-16
 */

#ifndef VULKANGRAPHICSWINDOW_H
#define VULKANGRAPHICSWINDOW_H

#include "config_vulkandisplay.h"

#ifdef _WIN32
#include "winGraphicsWindow.h"
typedef WinGraphicsWindow BaseGraphicsWindow;
#elif defined(HAVE_X11)
#include "x11GraphicsWindow.h"
typedef x11GraphicsWindow BaseGraphicsWindow;
#else
#include "graphicsWindow.h"
typedef GraphicsWindow BaseGraphicsWindow;
#endif

/**
 * A single graphics window for rendering to using the Vulkan API.  It manages
 * a VkSurface for the OS-specific base window implementation, as well as a
 * swapchain.
 */
class EXPCL_VULKANDISPLAY VulkanGraphicsWindow : public BaseGraphicsWindow {
public:
  VulkanGraphicsWindow(GraphicsEngine *engine, GraphicsPipe *pipe,
                       const std::string &name,
                       const FrameBufferProperties &fb_prop,
                       const WindowProperties &win_prop,
                       int flags,
                       GraphicsStateGuardian *gsg,
                       GraphicsOutput *host);
  virtual ~VulkanGraphicsWindow();

  virtual void clear(Thread *current_thread);
  virtual bool begin_frame(FrameMode mode, Thread *current_thread);
  virtual void end_frame(FrameMode mode, Thread *current_thread);

  virtual void begin_flip();
  virtual void ready_flip();
  virtual void end_flip();

protected:
  virtual void close_window();
  virtual bool open_window();

  bool setup_render_pass();

  void destroy_swapchain();
  bool create_swapchain();

private:
  VkSurfaceKHR _surface;
  VkSwapchainKHR _swapchain;
  VkRenderPass _render_pass;
  int _current_clear_mask;

  // We'll need these to synchronize the rendering with the presentation.
  VkSemaphore _render_complete;
  VkSemaphore _image_available;

  LVecBase2i _swapchain_size;
  VkSurfaceFormatKHR _surface_format;

  struct SwapBuffer {
    VulkanTextureContext *_tc;
    VkFramebuffer _framebuffer;
  };
  typedef pvector<SwapBuffer> SwapBuffers;
  SwapBuffers _swap_buffers;
  uint32_t _image_index;
  VkImageLayout _final_layout;

  VulkanTextureContext *_ms_color_tc = nullptr;
  VkSampleCountFlagBits _ms_count = VK_SAMPLE_COUNT_1_BIT;

  VulkanTextureContext *_depth_stencil_tc;
  VkFormat _depth_stencil_format;
  VkImageAspectFlags _depth_stencil_aspect_mask;

public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    BaseGraphicsWindow::init_type();
    register_type(_type_handle, "VulkanGraphicsWindow",
                  BaseGraphicsWindow::get_class_type());
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

private:
  static TypeHandle _type_handle;
};

#include "vulkanGraphicsWindow.I"

#endif
