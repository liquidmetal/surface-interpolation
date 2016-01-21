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

vector<vector<float> > eye(int n, float val=1)
{
  vector<vector<float> > identity;
  vector<float> dummy(n);

  int i;
  for(i=0;i<n;i++)
  {
    dummy[i]=val;
    identity.push_back(dummy);
    dummy[i] = 0;
  }
  return identity;
}

vector<vector<float> > matAdd(vector<vector<float> > A, vector<vector<float> > B) {
  vector<vector<float> > res;
  vector<float> dummy(A.size());
  int i, j;
  for(i = 0; i < A.size(); i++) {
    res.push_back(dummy);
    for(j = 0; j < A[0].size(); j++) {
      res[i][j] = A[i][j] + B[i][j];
    }
  }
  return res;
}

vector<vector<float> > transpose(vector<vector<float> > A)
{
  int i,j;
  vector<vector<float> > T;
  vector<float> dummy(A.size());

  for(i=0;i<A[0].size();i++)
  {
    T.push_back(dummy);
    for(j=0;j<A.size();j++)
    {
      T[i][j]=A[j][i];
    }
  }
  return T;
}

vector<float> ones(int l)
{
  vector<float> res;
  for(int i=0;i<l;i++)
  {
    res.push_back(1);
  }
  return res;
}

vector<vector<float> > concatThree(vector<float> a, vector<float> b, vector<float> c)
{
  vector<vector<float> > res;
  res.push_back(a);
  res.push_back(b);
  res.push_back(c);
  return transpose(res);
}

vector<vector<float> > concatTwoMatsSide(vector<vector<float> > A, vector<vector<float> > B) {
  vector<vector<float> > res;
  vector<float> dummy;
  int i;
  for(i = 0; i < A.size(); i++) {
    dummy.clear();
    dummy = A[i];
    dummy.insert(dummy.end(), B[i].begin(), B[i].end());
    res.push_back(dummy);
  }
  return res;
}

vector<vector<float> > concatTwoMatsBottom(vector<vector<float> > A, vector<vector<float> > B) {
  vector<vector<float> > res = A;
  for(int i=0;i<B.size();i++)
  {
    res.push_back(B[i]);
  }
  return res;
}

vector<vector<float> > matLog(vector<vector<float> > v) {
  vector<vector<float> > res = v;
  int i, j;
  for(i = 0; i < v.size(); i++) {
    for(j = 0; j < v[0].size(); j++) {
      res[i][j] = log(v[i][j]);
    }
  }
  return res;
}

vector<vector<float> > elementWiseMatMul(vector<vector<float> > A, vector<vector<float> > B) {
  int i, j;
  vector<vector<float> > res = A;
  for(i = 0; i < A.size(); i++) {
    for(j = 0; j < A[0].size(); j++) {
      res[i][j] = A[i][j]*B[i][j];
    }
  }
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

vector<vector<float> > thin_plate_spline(vector<vector<int> > x1, vector<vector<int> > x2, vector<vector<int> > y1,vector<vector<int> > y2, float log_fudge = 1) {
  vector<vector<float> > rr, res;
  rr = euclidean(x1, x2, y1, y2);
  res = elementWiseMatMul(elementWiseMatMul(rr, rr), matLog(rr));
  int i, j;
  for(i = 0; i < rr.size(); i++) {
    for(j = 0; j < rr[0].size(); j++) {
      if(rr[i][j] == 0) {
        res[i][j] = log_fudge;
      }
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
  vector<vector<float> > basis, mat;
  vector<float> ff;

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
      basis=thin_plate_spline(xres[0], xres[1], yres[0], yres[1], log_fudge);
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

  basis=matAdd(basis,eye(basis.size(),lambda));

  if(poly == 0) {
    mat = basis;
    ff = zi;
  }
  else if(poly == 1) {
    vector<float> xi_float(xi.begin(), xi.end());
    vector<float> yi_float(yi.begin(), yi.end());

    vector<vector<float> > q = concatThree(ones(xi.size()), xi_float, yi_float);
    vector<vector<float> > q_dash = transpose(q);
    vector<vector<float> > mat = concatTwoMatsBottom(concatTwoMatsSide(basis, q), concatTwoMatsSide(q_dash, eye(3, 0)));
    ff = zi;
    ff.push_back(0);
    ff.push_back(0);
    ff.push_back(0);
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
