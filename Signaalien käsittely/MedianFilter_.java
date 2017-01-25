import ij.*;
import ij.process.*;
import ij.gui.*;
import java.awt.*;
import ij.plugin.*;
import ij.plugin.frame.*;
import ij.plugin.filter.*; 
import java.util.Arrays;

public class MedianFilter_ implements PlugInFilter {
 ImagePlus imp;

 public int setup(String arg, ImagePlus imp) {
  this.imp = imp;
  return DOES_8G;
  }

 public void run(ImageProcessor ip) {
  int w=ip.getWidth();
  int h=ip.getHeight();
  ImageProcessor copy=ip.duplicate();
  // Ikkunan koko
  int L = 5;
  // Ikkunan luvut aputaulukkoon
  int[] window = new int[L*L];
  // Ikkunan keskipiste (x, y)
  for(int y=L/2; y<h-L/2; y++) {
   
   for(int x=L/2; x<w-L/2; x++) {
  
    int k=0; 

    for(int j=-L/2; j<=L/2; j++) {
    
      for(int i=-L/2; i<=L/2; i++) {
       
       window[k]=copy.getPixel(x+i, y+j);
       k++;
       }
      }
   // Järjestetään aputaulukko suuruusjärjestykseen
   Arrays.sort(window);
   // Muutetaan ikkunan origo mediaaniksi
   // Lasketaan jakojäännös kahdella jaettaessa x%2.
   // Jos jakojäännös == 0, lukuja on parillinen määrä
   if (window.length % 2 == 0) {
    ip.putPixel(x, y, (window[window.length/2-1]+window[window.length/2])/2);
    }
 // Pariton määrä lukuja
   else {
    ip.putPixel(x, y, window[window.length/2]);
    }
   }
  }
 imp.updateAndDraw();
 }
} 
