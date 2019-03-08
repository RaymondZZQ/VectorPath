#pragma once

#include "opencv2/core/core.hpp"

#include "windows.h"

#include "Gdiplus.h"
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

class _gdiplus_initializer;

class PotraceWrapper {
public:
  PotraceWrapper();
  ~PotraceWrapper();

  bool trace(const cv::Mat *image);
  Gdiplus::GraphicsPath *getpath() {
    if (m_pTracedPath)
      return m_pTracedPath->Clone();
    else
      return NULL;
  };

private:
  /* ���Կ������ߵ�Բ���̶�,ȡֵ��Χ[0.0, 1.3334],ֵԽ������ԽԲ��
          The alphamax parameter is a threshold for the detection of corners.
          It controls the smoothness of the traced curve, as shown in Figure 9.
          The current default is 1.0. The useful range of this parameter
          is from 0.0 (polygon) to 1.3334 (no corners).*/
  double m_alphaMax;

  /* �ӵ������ֵ
    The turdsize parameter can be used to ��despeckle��
     the bitmap to be traced,
     by removing all curves whose enclosed
     area is below the given threshold.*/
  int m_turdSize;

  /* ת�����
    The turnpolicy parameter determines how to
     resolve ambiguities during decomposition
     of bitmaps into paths.
          - POTRACE_TURNPOLICY_BLACK: prefers to connect black (foreground)
    components.
          - POTRACE_TURNPOLICY_WHITE: prefers to connectwhite (background)
    components.
          - POTRACE_TURNPOLICY_LEFT: always take a left turn.
          - POTRACE_TURNPOLICY_RIGHT: always take a right turn.
          - POTRACE_TURNPOLICY_MINORITY: prefers to connect the color (black or
    white) that occurs least frequently in a local neighborhood of the current
    position.
          - POTRACE_TURNPOLICY_MAJORITY: prefers to connect the color (black or
    white) that occurs most frequently in a local neighborhood of the current
    position.
          - POTRACE_TURNPOLICY_RANDOM: choose pseudo-randomly. */
  int m_turnpolicy;

  /* �Ƿ����Ż�����,����Ԫ������
   The opticurve parameter is a boolean flag
          that controls whether Potrace will attempt
          to ��simplify�� the final curve by reducing
          the number of Bezier curve segments.*/
  int m_opticurve;
  /* �Ż����̶߳�
   The opttolerance parameter defines the amount of error allowed in this
   simplification. The current default is 0.2. Larger values tend to decrease
   the number of segments, at the expense of less accuracy. The useful range is
   from 0 to infinity, although in practice one would hardly choose values
   greater than 1 or so. For most
          purposes, the default value is a good tradeoff between space and
   accuracy.*/
  double m_curveTolerance;

  // ��ͼ����ж�ֵ������ֵ
  int m_threshold;

  // VectorPath m_curvesData;

  Gdiplus::GraphicsPath *m_pTracedPath;

  double m_width;
  double m_height;

private:
  static _gdiplus_initializer _initializer_;
};

// ������ʼ��Gdiplus
class _gdiplus_initializer {
public:
  _gdiplus_initializer() {
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
  }
  ~_gdiplus_initializer() { GdiplusShutdown(gdiplusToken); }

private:
  ULONG_PTR gdiplusToken;
  GdiplusStartupInput gdiplusStartupInput;
};