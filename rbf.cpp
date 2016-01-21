#include<iostream>
#include<string>
#include<ctime>
#include<vector>
#include<stdio.h>
#include<math.h>

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

float square(float x)
{
  return pow(x, 2);
}

void display(vector<vector<float> > v) {
  int i, j;
  for(i = 0; i < v.size(); i++) {
    for(j = 0; j < v[0].size(); j++) {
      printf("%f ", v[i][j]);
    }
    printf("\n");
  }
}

void display(vector<vector<int> > v) {
  int i, j;
  for(i = 0; i < v.size(); i++) {
    for(j = 0; j < v[0].size(); j++) {
      printf("%d ", v[i][j]);
    }
    printf("\n");
  }
}

float mean(vector<vector<float> > v) {
  int i, j;
  float res;
  for(i = 0; i < v.size(); i++) {
    for(j= 0; j < v[0].size(); j++) {
      res += v[i][j];
    }
  }
  res /= v.size()*v[0].size();
  return res;
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

vector<vector<float> > euclidean(vector<vector<int> > x1, vector<vector<int> > x2, vector<vector<int> > y1,vector<vector<int> > y2)
{
  vector<vector<float> > res;
  vector<float> dummy(x1[0].size());
  int i, j;
  for(i = 0; i < x1.size(); i++) {
    res.push_back(dummy);
    for(j = 0; j < x1[0].size(); j++) {
      res[i][j] = sqrt(square(x1[i][j]-x2[i][j]) + square(y1[i][j]-y2[i][j]));
    }
  }
  return res;
}

float rbf(vector<int> xi, vector<int> yi, vector<float> zi, vector<vector<int> > xx, vector<vector<int> > yy, string basis_func="euclidean", float lambda=0, float log_fudge=0)
{
  clock_t begin=clock();
  vector<vector<vector<int> > > yres = meshgrid(xi);
  vector<vector<vector<int> > > xres = meshgrid(yi);
  int poly, i,j;
  vector<vector<float> > basis;

  display(xres[0]);
  display(xres[1]);
  display(yres[0]);
  display(yres[1]);

  switch (hashit(basis_func)) {
    case euclideanH:
      basis=euclidean(xres[0], xres[1], yres[0], yres[1]);
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

  if(lambda != 0) {
    vector<vector<float> > scale;
    scale = euclidean(xres[0], xres[1], yres[0], yres[1]);
    float scale_mean = mean(scale);
    lambda = square(scale_mean) * lambda;
    printf("%f\n", lambda);
  }

  clock_t end=clock();
  float elapsed_sec=double(end-begin)/CLOCKS_PER_SEC;
  printf("Elapsed time: %f\n",elapsed_sec);

  return 0;
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
  display(xx);
  display(yy);

  float zz = rbf(xi, yi, zi, xx, yy);
  printf("%f\n", zz);
}
