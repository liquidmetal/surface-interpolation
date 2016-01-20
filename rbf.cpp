#include<iostream>
#include<string>
#include<ctime>
#include<vector>


using namespace std;

enum string_code {
  euclideanH,
  thin_plate_splineH,
  gaussianH,
  multiquadraticH,
  triharmonic_splineH
};

string_code hashit (string const& inString) {
  if (inString == "euclidean") return euclideanH;
  if (inString == "thin_plate_spline") return thin_plate_splineH;
  if (inString == "gaussian") return gaussianH;
  if (inString == "multiquadratic") return multiquadraticH;
  if (inString == "triharmonic_spline") return triharmonic_splineH;
}

vector<vector<vector<int> > > meshgrid(vector<int> v)
{
  int i, j;
  vector<vector<int> > x1, x2;
  vector<int> dummy;
  for(i = 1; i <= v.size(); i++) {
    for(j = 1; j <= v.size(); j++) {
      dummy.push_back(v[i-1]);
    }
    x2.push_back(dummy);
    x1.push_back(v);
    dummy.clear();
  }
  vector<vector<vector<int> > > res;
  res.push_back(x1);
  res.push_back(x2);
  return res;
}



float rbf(vector<int> xi, vector<int> yi, vector<float> zi, vector<vector<int> > xx, vector<vector<int> > yy, string basis_func="euclidean", float lambda=0, float log_fudge=0)
{
  clock_t begin=clock();
  vector<vector<vector<int> > > yres = meshgrid(xi);
  vector<vector<vector<int> > > xres = meshgrid(yi);
  int poly;

  switch (hashit(basis_func)) {
    case euclideanH:
      // euclidean(x1, x2, y1, y2, log_fudge);
      poly=1;
      break;
    case thin_plate_splineH:
      //TODO
      poly=1;
      break;
    case gaussianH:
      //TODO
      poly=0;
      break;
    case multiquadraticH:
      //TODO
      poly=0;
      break;
    case triharmonic_splineH:
      //TODO
      poly=0;
      break;
  }

  clock_t end=clock();
  float elapsed_sec=double(end-begin)/CLOCKS_PER_SEC;
  printf("%f",elapsed_sec);
}

int main()
{
  vector<int> xi, yi;
  vector<float> zi;
  xi.push_back(4);
  xi.push_back(4);
  xi.push_back(8);
  xi.push_back(7);
  yi.push_back(1);
  yi.push_back(6);
  yi.push_back(7);
  yi.push_back(8);
  zi.push_back(0.1088);
  zi.push_back(0.3083);
  zi.push_back(0.3083);
  zi.push_back(0.3083);

  vector<vector<int> > xx, yy;
  vector<int> dummy, dummy1;
  int i, j;
  for(i = 1; i <= 11; i++) {
    for(j = 1; j <= 11; j++) {
      dummy.push_back(i);
      dummy1.push_back(j);
    }
    xx.push_back(dummy);
    yy.push_back(dummy1);
    dummy.clear();
    dummy1.clear();
  }
  for(i = 0; i < 11; i++) {
    for(j = 0; j < 11; j++) {
      printf("%d ", xx[i][j]);
    }
    printf("\n");
  }
  for(i = 0; i < 11; i++) {
    for(j = 0; j < 11; j++) {
      printf("%d ", yy[i][j]);
    }
    printf("\n");
  }
  // vector<vector<vector<int> > > xres = meshgrid(yi);
  // vector<vector<vector<int> > > yres = meshgrid(xi);
  // for(i = 0; i < xres[0][0].size(); i++) {
  //   for(j = 0; j < xres[0][0].size(); j++) {
  //     printf("%d ", xres[0][i][j]);
  //   }
  //   printf("\n");
  // }
  // for(i = 0; i < xres[1][0].size(); i++) {
  //   for(j = 0; j < xres[1][0].size(); j++) {
  //     printf("%d ", xres[1][i][j]);
  //   }
  //   printf("\n");
  // }
}
