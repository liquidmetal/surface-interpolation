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

void display(vector<float> v) {
  int i;
  for(i = 0; i < v.size(); i++) {
    printf("%f ", v[i]);
  }
  printf("\n");
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

vector<vector<float> > elementWiseMatMul(vector<vector<float> > A, vector<vector<float> > B, float c = 1) {
  int i, j;
  vector<vector<float> > res = A;
  for(i = 0; i < A.size(); i++) {
    for(j = 0; j < A[0].size(); j++) {
      res[i][j] = A[i][j]*B[i][j]*c;
    }
  }
  return res;
}

vector<vector<float> > constantMatAdd(vector<vector<float> > A, float c) {
  int i, j;
  vector<vector<float> > res = A;
  for(i = 0; i < A.size(); i++) {
    for(j = 0; j < A[0].size(); j++) {
      res[i][j] += c;
    }
  }
  return res;
}

vector<vector<float> > constantMatMul(vector<vector<float> > A, float c) {
  int i, j;
  vector<vector<float> > res = A;
  for(i = 0; i < A.size(); i++) {
    for(j = 0; j < A[0].size(); j++) {
      res[i][j] *= c;
    }
  }
  return res;
}

vector<vector<float> > expMat(vector<vector<float> > A) {
  int i, j;
  vector<vector<float> > res = A;
  for(i = 0; i < A.size(); i++) {
    for(j = 0; j < A[0].size(); j++) {
      res[i][j] = exp(A[i][j]);
    }
  }
  return res;
}

vector<float> slice(vector<float> v, int start_index, int end_index) {
  vector<float> res;
  int i;
  for(i = start_index; i < end_index; i++)
  {
    res.push_back(v[i]);
  }
  return res;
}

vector<vector<vector<float> > > meshgrid(vector<float> v)
{
  int i, j;
  vector<vector<float> > x1, x2;
  vector<float> dummy;
  for(i = 1; i <= v.size(); i++) {
    for(j = 1; j <= v.size(); j++) {
      dummy.push_back(v[i-1]);
    }
    x2.push_back(dummy);
    x1.push_back(v);
    dummy.clear();
  }
  vector<vector<vector<float> > > res;
  res.push_back(x1);
  res.push_back(x2);
  return res;
}

vector<vector<float> > euclidean(vector<vector<float> > x1, vector<vector<float> > x2, vector<vector<float> > y1,vector<vector<float> > y2)
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

vector<vector<float> > thin_plate_spline(vector<vector<float> > x1, vector<vector<float> > x2, vector<vector<float> > y1,vector<vector<float> > y2, float log_fudge = 1) {
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

vector<vector<float> > gaussian(vector<vector<float> > x1, vector<vector<float> > x2, vector<vector<float> > y1,vector<vector<float> > y2, float log_fudge = 1) {
  vector<vector<float> > rr, res;
  rr = euclidean(x1, x2, y1, y2);
  float aa = log_fudge;
  res = expMat(elementWiseMatMul(rr, rr, aa));
  return res;
}

vector<vector<float> > multiquadratic(vector<vector<float> > x1, vector<vector<float> > x2, vector<vector<float> > y1,vector<vector<float> > y2, float log_fudge = 1) {
  vector<vector<float> > rr, res;
  rr = euclidean(x1, x2, y1, y2);
  float cc = log_fudge;
  res = elementWiseMatMul(rr, rr);
  vector<vector<float> > cc_square = res;
  for(int i=0;i<res.size();i++)
  {
    for(int j=0;j<res[0].size();j++)
    {
      cc_square[i][j]=cc*cc;
    }
  }
  res=matAdd(res,cc_square);
  return res;
}

vector<vector<float> > triharmonic_spline(vector<vector<float> > x1, vector<vector<float> > x2, vector<vector<float> > y1,vector<vector<float> > y2, float log_fudge = 0) {
  vector<vector<float> > rr, res;
  rr = euclidean(x1, x2, y1, y2);
  float aa = log_fudge;
  res = elementWiseMatMul(rr, rr);
  res = elementWiseMatMul(res,res);
  res=elementWiseMatMul(res,matLog(rr));
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

vector<vector<float> > rbf(vector<float> xi, vector<float> yi, vector<float> zi, vector<vector<float> > xx, vector<vector<float> > yy, string basis_func="euclidean", float lambda=0, float log_fudge=0)
{
  clock_t begin=clock();
  vector<vector<vector<float> > > yres = meshgrid(xi);
  vector<vector<vector<float> > > xres = meshgrid(yi);
  int poly_order, i,j;
  vector<vector<float> > basis, mat;
  vector<float> ff;

  switch (hashit(basis_func)) {
    case euclideanH:
      basis=euclidean(xres[0], xres[1], yres[0], yres[1]);
      poly_order=1;
      break;
    case thin_plate_splineH:
      basis=thin_plate_spline(xres[0], xres[1], yres[0], yres[1], log_fudge);
      poly_order=1;
      break;
    case gaussianH:
      basis=gaussian(xres[0], xres[1], yres[0], yres[1], log_fudge);
      poly_order=0;
      break;
    case multiquadraticH:
      basis=multiquadratic(xres[0], xres[1], yres[0], yres[1], log_fudge);
      poly_order=0;
      break;
    case triharmonic_splineH:
    basis=triharmonic_spline(xres[0], xres[1], yres[0], yres[1], log_fudge);
      poly_order=0;
      break;
  }

  if(lambda != 0) {
    vector<vector<float> > scale;
    scale = euclidean(xres[0], xres[1], yres[0], yres[1]);
    float scale_mean = mean(scale);
    lambda = square(scale_mean) * lambda;
  }

  basis=matAdd(basis,eye(basis.size(),lambda));

  if(poly_order == 0) {
    mat = basis;
    ff = zi;
  }
  else if(poly_order == 1) {
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

  vector<float> lam_c;
  lam_c.push_back(-0.0006);
  lam_c.push_back(0.0011);
  lam_c.push_back(0.0017);
  lam_c.push_back(-0.0023);
  lam_c.push_back(0.1245);
  lam_c.push_back(-0.0113);
  lam_c.push_back(0.0363);

  vector<float> lam = slice(lam_c, 0, lam_c.size()-3*poly_order);
  vector<float> c = slice(lam_c, lam_c.size()-2*poly_order-1, lam_c.size());
  vector<vector<float> > poly, zz=xx;

  if(poly_order>0) {
    poly = constantMatAdd(matAdd(constantMatMul(xx, c[1]), constantMatMul(yy, c[2])), c[0]);
  }
  else {
    poly = xx;
    for(i=0;i<xx.size();i++)
    {
      for(j=0;j<xx[0].size();j++)
      {
        poly[i][j]=0;
      }
    }
  }

  for(i=0;i<xx.size();i++)
  {
    for(j=0;j<xx[0].size();j++)
    {
      zz[i][j]=0;
    }
  }

  int ii, kk;
  vector<vector<vector<float> > > container;
  vector<vector<float> > temp;
  vector<float> content;
  content.push_back(0);
  temp.push_back(content);
  container.push_back(temp);
  container.push_back(temp);
  container.push_back(temp);
  container.push_back(temp);

  for(ii = 0; ii < xx.size()*xx[0].size(); ii++) {
    for(kk = 0; kk < zi.size(); kk++) {
      container[0][0][0] = xx[ii%xx.size()][ii/xx.size()];
      container[1][0][0] = xi[kk];
      container[2][0][0] = yy[ii%xx.size()][ii/xx.size()];
      container[3][0][0] = yi[kk];
      switch (hashit(basis_func)) {
        case euclideanH:
          basis=euclidean(container[0], container[1], container[2], container[3]);
          break;
        case thin_plate_splineH:
          basis=thin_plate_spline(container[0], container[1], container[2], container[3], log_fudge);
          break;
        case gaussianH:
          basis=gaussian(container[0], container[1], container[2], container[3], log_fudge);
          break;
        case multiquadraticH:
          basis=multiquadratic(container[0], container[1], container[2], container[3], log_fudge);
          break;
        case triharmonic_splineH:
        basis=triharmonic_spline(container[0], container[1], container[2], container[3], log_fudge);
          break;
      }
      zz[ii%zz.size()][ii/zz.size()] += lam[kk]*basis[0][0];
    }
  }

  zz=matAdd(zz,poly);

  clock_t end=clock();
  float elapsed_sec=double(end-begin)/CLOCKS_PER_SEC;
  printf("Elapsed time: %f\n",elapsed_sec);

  return zz;
}

int main()
{
  vector<float> xi, yi;
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

  vector<vector<float> > xx, yy;
  vector<float> dummy, dummy1;
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

  vector<vector<float> > zz = rbf(xi, yi, zi, xx, yy, "euclidean", 1, 2);
  display(zz);
}
