#include <awful/Rasterization.h>
#include <awful/Renderer.h>

void fillBottomFlatTriangle(CgmVec2 p1, CgmVec2 p2, CgmVec2 p3) {
  float invslope1 = (p2.x - p1.x) / (p2.y - p1.y);
  float invslope2 = (p3.x - p1.x) / (p3.y - p1.y);

  float curx1 = p1.x;
  float curx2 = p1.x;

  for (int scanlineY = p1.y; scanlineY <= p2.y; scanlineY++) {
    RendererDrawZLine(CgmVec2_init((int)curx1, scanlineY),
                      CgmVec2_init((int)curx2, scanlineY), 0.0F, 0.0F);
    curx1 += invslope1;
    curx2 += invslope2;
  }
}

void fillTopFlatTriangle(CgmVec2 p1, CgmVec2 p2, CgmVec2 p3) {
  float invslope1 = (p3.x - p1.x) / (p3.y - p1.y);
  float invslope2 = (p3.x - p2.x) / (p3.y - p2.y);

  float curx1 = p3.x;
  float curx2 = p3.x;

  for (int scanlineY = p3.y; scanlineY > p1.y; scanlineY--) {
    RendererDrawZLine(CgmVec2_init((int)curx1, scanlineY),
                      CgmVec2_init((int)curx2, scanlineY), 1.0F, 1.0F);
    curx1 -= invslope1;
    curx2 -= invslope2;
  }
}

void sortVerticesAscendingByY(CgmVec2 points[]) {
    CgmVec2 p1 = CgmVec2_init_even(0);
    CgmVec2 p2 = CgmVec2_init_even(0);
    CgmVec2 p3 = CgmVec2_init_even(0);

    for(int i=0; i<3; i++){
        if(points[i].y > p1.y){
            p1 = points[i];
        }else if(points[i].y > p2.y){
            p2 = points[i];
        }else{
            p3 = points[i];
        }
    }

    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
}

void RasterDrawTri(CgmVec2 p1, CgmVec2 p2, CgmVec2 p3) {
  /* at first sort the three vertices by y-coordinate ascending so p1 is the
   * topmost vertice */
  CgmVec2 points[] = {p1, p2, p3};
  sortVerticesAscendingByY(points);

  /* here we know that p1.y <= p2.y <= p3.y */
  /* check for trivial case of bottom-flat triangle */
  if (points[1].y == points[2].y) {
    fillBottomFlatTriangle(points[0], points[1], points[2]);
  }

  /* check for trivial case of top-flat triangle */
  else if (points[0].y == points[1].y) {
    fillTopFlatTriangle(points[0], points[1], points[2]);
  } else {
    /* general case - split the triangle in a topflat and bottom-flat one */
    // Vertice v4 = new Vertice((int)(vt1.x + ((float)(vt2.y - vt1.y) / (float)(vt3.y - vt1.y)) * (vt3.x - vt1.x)), vt2.y);
    CgmVec2 p4 = CgmVec2_init((int)(points[0].x + ((float)(points[1].y - points[0].y) / (float)(points[2].y - points[0].y)) * (points[2].x - points[0].x)), points[1].y);
    fillBottomFlatTriangle(points[0], points[1], p4);
    fillTopFlatTriangle(points[1], p4, points[2]);
  }
}