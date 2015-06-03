//
//  Tensor3D.cpp
//  Mugen
//
//  Created by Diego Andrade on 5/12/15.
//  Copyright (c) 2015 CMU. All rights reserved.
//

#include "Tensor3D.h"


/*void Tensor3D::Tensor3D(const double M0, double m1, double m2,double m3, double m4, double m5)
{
  //  Tensor3D::m0 = M0;
   // Tensor3D::m1 = m1;
   // Tensor3D::m2 = m2;
   // Tensor3D::m3 = m3;
  //  Tensor3D::m4 = m4;
  //  Tensor3D::m5 = m5;
    
    A[0][0] = M0;
    A[0][1] = m1;
    A[0][2] = m2;
    A[1][0] = m1;
    A[1][1] = m3;
    A[1][2] = m4;
    A[2][0] = m2;
    A[2][1] = m4;
    A[2][2] = m5;
    
    R[0][0] = m0;
    R[0][1] = m1;
    R[0][2] = m2;
    R[1][0] = m1;
    R[1][1] = m3;
    R[1][2] = m4;
    R[2][0] = m2;
    R[2][1] = m4;
    R[2][2] = m5;

}*/

void Tensor3D::printTensor()
{
    cout << " --------------------------------------------------------------" << endl;
    cout << setprecision(5) << fixed << "\tL[0][0]: " << L[0][0] << setw(5) << "\tL[0][1]: " << L[0][1] << setw(5) << "\tL[0][2]: " << L[0][2] << setw(8) << endl;
    cout << "\tL[1][0]: " << L[1][0] << "\tL[1][1]: " << L[1][1] << "\tL[1][2]: " << L[1][2] << endl;
    cout << "\tL[2][0]: " << L[2][0] << "\tL[2][1]: " << L[2][1] << "\tL[2][2]: " << L[2][2] << endl;
    cout << endl;
    cout << "\tR[0][0]: " << R[0][0] << "\tR[0][1]: " << R[0][1] << "\tR[0][2]: " << R[0][2] << endl;
    cout << "\tR[1][0]: " << R[1][0] << "\tR[1][1]: " << R[1][1] << "\tR[1][2]: " << R[1][2] << endl;
    cout << "\tR[2][0]: " << R[2][0] << "\tR[2][1]: " << R[2][1] << "\tR[2][2]: " << R[2][2] << endl;
    cout << " --------------------------------------------------------------" << endl;
    
}



