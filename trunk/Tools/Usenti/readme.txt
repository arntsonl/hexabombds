
         -------------------------------------------------------
       //                                                       \\
      ||        UU     UU      ss                                ||
      ||        UUU    UU     s  s                               ||
      ||        UU U   UU    s  s      nnn                       ||
      ||        UU  U  UU    s     ee     n   ttt   i   i        ||
      ||        UU   U UU   s s     e   nn   t   t  i  i         ||
      ||        UU    UUU   s  s    e     n  t   t   ii          ||
      ||        UU     UU  s    s   e  nnn   tttt   i i          ||
      ||                                     t      i i          ||
      ||                                     t      ii           ||
      ||                                                         ||
      ||=========================================================||
      ||                 Usenti: a bitmap editor                 ||
      ||                          v1.7.4                         ||
      ||                 (last update: 21-03-2006)               ||
      ||                  (started: 10-10-2002)                  ||
       \\_______________________________________________________//


Usenti is:
- an 8bit bitmap editor for Windows with nearly all the capabitities 
  of MS-Paint, plus a few extras like proper palette editor,
  adjustable grid settings for easy tile-aligning and mouse-wheel 
  use for zooming and moving aruond the image.
- using standard Windows-interface functionality like undo, toolbars, 
  profile-settings, drag&drop and clipboard support.
- capable of exporting to GBA source code (C/S/BIN/GBFS).
- able to do some advanced (*cough*yeah right*cough*) palette 
  remapping like swapping and sorting.

Usenti is NOT:
- a photo-editor. You're not supposed to edit photos at the pixel-
  level. You can try, of course, but I give no guarantees.
- expensive. In fact, it's absolutely free :).
- restricted to 8bit bitmaps. Though internally working with an
  8bit palette, images at other bitdepths can be used as well, although
  true-color images will be quantized to 256 colors.

Usenti's primary purpose:
  To create/modify simple graphics where editing is done by the 
  pixel and easy control over the palette is essential. And we all
  know how woefully inadequate MS-Paint is there.
  Initially intended specifically for GBA graphics, it should work
  fine for other purposes (like web-graphics) as well.

Platforms:
  Win32.

Usable image formats:
  BMP, PCX, PNG, TGA

Last changes:
- Un-added shortkeys for tools; they screwed up the text tool :(
- Added tile reducer
- Completely rewritten file routines
- Completely new GBA exporter, with mapping options, compression and 
  everything.
- Added tile rearrange function
- Color quantizer for true-color images, woohoo!
- Color adjustment
(- fixed a few alignment/padding issues)

Feedback:
  Of course, feedback is very much appreciated, but I had hoped that
  after v1.5 I could spend some times on other projects. New bugs or 
  misfeatures I will take into consideration ASAP, but full feature 
  requests could take a while, depending on my state of mind.

	- Cearn

mail: daytshen at hotmail dot com
url: http://user.chem.tue.nl/jakvijn/

The screenshot is taken from the mode7d demo from the TONC tutorials, 
which can be found at
http://user.chem.tue.nl/jakvijn/tonc/index.htm

----------------------------------------------------------------------------------

PS: This is just a simple readme. For more details on features and how 
to work with Usenti, see usenti.chm.


