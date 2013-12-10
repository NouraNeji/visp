/*! \example tutorial-template-tracker-image.cpp */
#include <visp/vpDisplayGDI.h>
#include <visp/vpDisplayX.h>
#include <visp/vpImageIo.h>
#include <visp/vpTemplateTrackerSSDInverseCompositional.h>
#include <visp/vpTemplateTrackerWarpHomography.h>

int main()
{
#if defined(VISP_HAVE_X11) || defined(VISP_HAVE_GDI)
  vpImage<unsigned char> I;

  vpImageIo::readPGM(I, "pattern-template-tracker.pgm");

#ifdef UNIX
  vpDisplayX display;
#else
  vpDisplayGDI display;
#endif

  display.init(I,100,100,"Template tracker");
  vpDisplay::display(I);
  vpDisplay::flush(I);

  vpTemplateTrackerWarpHomography warp;

  vpTemplateTrackerSSDInverseCompositional tracker(&warp);

  tracker.setSampling(2,2);
  tracker.setLambda(0.001);
  tracker.setIterationMax(200);
  tracker.setPyramidal(2, 1);

  tracker.initClick(I);

  while(1){
    vpDisplay::display(I);
    tracker.track(I);

    tracker.display(I, vpColor::red);

    vpDisplay::flush(I);
    vpTime::wait(40);
  }
#endif
}
