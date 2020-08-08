////////////////////////////////////////////////////////////////////////////////
/// Bins the histogram using a honeycomb structure rotated by 90 degrees
/// compared to the original ROOT code

void HoneycombRot(TH2Poly* map, Double_t xstart, Double_t ystart, Double_t a,
                     Int_t k, Int_t s)
{
   // Add the bins
   Double_t numberOfHexagonsInTheRow;
   Double_t x[6], y[6];
   Double_t xloop, yloop, xtemp;
   xloop = xstart; yloop = ystart + a/2.0;
   for (int sCounter = 0; sCounter < s; sCounter++) {

      xtemp = xloop; // Resets the temp variable

      // Determine the number of hexagons in that row
      if(sCounter%2 == 0){numberOfHexagonsInTheRow = k;}
      else{numberOfHexagonsInTheRow = k - 1;}

      for (int kCounter = 0; kCounter <  numberOfHexagonsInTheRow; kCounter++) {

         // Go around the hexagon
         x[0] = xtemp;
         y[0] = yloop;
         x[1] = x[0];
         y[1] = y[0] + a;
         x[2] = x[1] + a*TMath::Sqrt(3)/2.0;
         y[2] = y[1] + a/2.0;
         x[3] = x[2] + a*TMath::Sqrt(3)/2.0;
         y[3] = y[1];
         x[4] = x[3];
         y[4] = y[0];
         x[5] = x[2];
         y[5] = y[4] - a/2.0;

         map->AddBin(6, y, x);

         // Go right
         xtemp += a*TMath::Sqrt(3);
      }

      // Increment the starting position
      if (sCounter%2 == 0) xloop += a*TMath::Sqrt(3)/2.0;
      else                 xloop -= a*TMath::Sqrt(3)/2.0;
      yloop += 1.5*a;
   }
}
