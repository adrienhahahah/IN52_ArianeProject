/* -*- c-basic-offset: 3 -*-
 *
 * PANTHEON Project
 *
 * GREYC IMAGE
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex France
 *
 * This file is free software. You can use it, distribute it
 * and/or modify it. However, the entire risk to the quality
 * and performance of this program is with you.
 *
 * For more information, refer to:
 * http://www.greyc.ensicaen.fr/EquipeImage/Pandore/
 */

/*
 * @author Régis Clouard - 2001-02-01
 */

/*
 * @file example0.cc
 * Example of operator source.
 */


#include <stdio.h>
#include <pandore.h>
using namespace pandore;

/*      
 * Morphologie mathematique:
 * Erosion d'une image: recherche du minimum parmi les voisins.
 */
Errc Erosion( const Img2duc &ims, Img2duc &imd, ) {
   Point2d p;
   Img2duc::ValueType min,val;
  
   imd.Frame(0,1);
   if (connexite == 4){
      for (p.y=1; p.y<ims.Height()-1; p.y++)
	 for (p.x=1; p.x<ims.Width()-1; p.x++) {
	    min=ims[p];
	    for (int v=0; v<4; v++){
	       if ((val=ims[p+v4[v]]) < min)
		  min = val;	
	    }
	    imd[p] = min;
	 }
   } else { // connexite == 8.
      for (p.y=1; p.y<ims.Height()-1; p.y++)
	 for (p.x=1; p.x<ims.Width()-1; p.x++) {
	    min=ims[p];
	    for (int v=0; v<8; v++){
	       if ((val=ims[p+v8[v]]) < min)
		  min = val;	
	    }
	    imd[p] = min;
	 }
   }
   return SUCCESS;
}

#ifdef MAIN
#define USAGE   "usage: %s connexity [-m mask] [im_in|-] [im_out|-]"
#define PARC    0
#define FINC    1
#define FOUTC   1
#define MASK    1

int main(int argc,char* argv[]) {
   Errc result;			// The result code of the execution.
   Pobject *mask;		// The mask.
   Pobject *objin[FINC+1];	// The input objects;
   Pobject *objs[FINC+1];	// The source objects masked by mask.
   Pobject *objout[FOUTC+1];	// The output object unmasked by mask.
   Pobject *objd[FOUTC+1];	// The result object.
   char *parv[PARC+1];		// The input parameters.
  
   ReadArgs(argc,argv,PARC,FINC,FOUTC,&mask,objin,objs,objout,objd,parv,USAGE,MASK);
   switch(objs[0]->Type()){
   case Po_Img2duc :{
      Img2duc* const ims=(Img2duc*)objs[0];
      objd[0]=new Img2duc(ims->Props());
      Img2duc* const imd=(Img2duc*)objd[0];
     
      result=Erosion(*ims,*imd,));
   }break;
   default :
      PrintErrorFormat(objin,FINC);
      result =FAILURE;
   }
  
   if (result)
      WriteArgs(argc,argv,PARC,FINC,FOUTC,&mask,objin,objs,objout,objd,MASK);
   Exit(result);
   return 0;
}

#endif
