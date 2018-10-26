/ *  
 L i c e n s e   n o t e   o f   t h e   l i b c w l - s e r i e s   o f   l i b r a r i e s ,   w h i c h   p r o v i d e s   u t i l i t i e s   f o r  
 t h e   C W i s h l i s t ,   C W i s h l i s t B a s e ,   C W i s h l i s t U n c d e   a n d   C W i s h l i s t D e f l a t e   s t a n d a r d s .  
 ( c )   2 0 1 8   b y   C h r i s t i a n   E .   " c h r i s s x "   H � u � l e r  
 L i c e n s e d   t o   e v e r y b o d y   u n d e r   t h e   t e r m s   o f   t h e   G N U   G P L   v 3 ,   w h i c h   y o u   s h o u l d  
 h a v e   o b t a i n e d   t h i s   s o f t w a r e   w i t h .  
  
 T h i s   p i e c e   o f   s o f t w a r e   u s e s   t h e   l i b r a r y   " l i b d e f l a t e "   b y   E r i c   B i g g e r s .  
 H e r e   y o u   c a n   s e e   a   s e c t i o n   f r o m   i t s   l i c e n s e   a g r e e m e n t :  
  
 * * * Q U O T E * * *  
 P e r m i s s i o n   i s   h e r e b y   g r a n t e d ,   f r e e   o f   c h a r g e ,   t o   a n y   p e r s o n  
 o b t a i n i n g   a   c o p y   o f   t h i s   s o f t w a r e   a n d   a s s o c i a t e d   d o c u m e n t a t i o n   f i l e s  
 ( t h e   " S o f t w a r e " ) ,   t o   d e a l   i n   t h e   S o f t w a r e   w i t h o u t   r e s t r i c t i o n ,  
 i n c l u d i n g   w i t h o u t   l i m i t a t i o n   t h e   r i g h t s   t o   u s e ,   c o p y ,   m o d i f y ,   m e r g e ,  
 p u b l i s h ,   d i s t r i b u t e ,   s u b l i c e n s e ,   a n d / o r   s e l l   c o p i e s   o f   t h e   S o f t w a r e ,  
 a n d   t o   p e r m i t   p e r s o n s   t o   w h o m   t h e   S o f t w a r e   i s   f u r n i s h e d   t o   d o   s o ,  
 s u b j e c t   t o   t h e   f o l l o w i n g   c o n d i t i o n s :  
  
 T h e   a b o v e   c o p y r i g h t   n o t i c e   a n d   t h i s   p e r m i s s i o n   n o t i c e   s h a l l   b e  
 i n c l u d e d   i n   a l l   c o p i e s   o r   s u b s t a n t i a l   p o r t i o n s   o f   t h e   S o f t w a r e .  
 * * * Q U O T E   E N D * * *  
 * /  
  
 # i n c l u d e   " l i b c w l c p p . h "  
  
 u s i n g   n a m e s p a c e   l i b c w l c p p ;  
  
 l i b c w l c p p : : i t e m : : i t e m ( )  
 {  
 	 n a m e   =   u r l   =   w n u l l ;  
 }  
  
 l i b c w l c p p : : i t e m : : i t e m ( w s t r i n g   n a m e ,   w s t r i n g   u r l )  
 {  
 	 t h i s - > n a m e   =   n a m e ;  
 	 t h i s - > u r l   =   u r l ;  
 }  
  
 c o n s t   w c h a r _ t   * l i b c w l c p p : : i t e m : : t o _ s t r i n g ( )  
 {  
 	 r e t u r n   n a m e   ! =   w n u l l   & &   n a m e . l e n g t h ( )   ?   n a m e . c _ s t r ( )   :   u n n a m e d _ i t e m ;  
 }  
  
 b o o l   l i b c w l c p p : : i t e m : : e q u a l s ( i t e m   & i t m )  
 {  
 	 r e t u r n   ! n a m e . c o m p a r e ( i t m . n a m e )   & &   ! u r l . c o m p a r e ( i t m . u r l ) ;  
 }  
  
 b o o l   l i b c w l c p p : : i t e m : : e q u a l s ( v o i d   * o b j )  
 {  
 	 r e t u r n   e q u a l s ( * ( i t e m * ) o b j ) ;  
 }  
  
 i n t m a x _ t   l i b c w l c p p : : i t e m : : h a s h _ c o d e ( )  
 {  
 	 s i z e _ t   n l   =   n a m e . l e n g t h ( ) ;  
 	 s i z e _ t   u l   =   u r l . l e n g t h ( ) ;  
 	 i n t m a x _ t   n s   =   0 ;  
 	 i n t m a x _ t   u s   =   0 ;  
 	 f o r   ( s i z e _ t   i   =   0 ;   i   <   n l ;   i + + )  
 	 	 n s   + =   n a m e [ i ] ;  
 	 f o r   ( s i z e _ t   i   =   0 ;   i   <   u l ;   i + + )  
 	 	 u s   + =   u r l [ i ] ;  
 	 r e t u r n   n l   *   u l   *   n s   *   u s ;  
 }  
  
 b o o l   l i b c w l c p p : : i t e m : : o p e r a t o r = = ( i t e m   & i t m )  
 {  
 	 r e t u r n   e q u a l s ( i t m ) ;  
 }  
  
 b o o l   l i b c w l c p p : : i t e m : : o p e r a t o r ! = ( i t e m   & i t m )  
 {  
 	 r e t u r n   ! e q u a l s ( i t m ) ;  
 }  
  
 u l o n g   l i b c w l c p p : : i t e m : : l e n g t h ( )  
 {  
 	 r e t u r n   n a m e . l e n g t h ( )   +   u r l . l e n g t h ( ) ;  
 }  
  
 b y t e *   l i b c w l c p p : : i t e m : : t o _ b y t e s ( c h a r   * f o r m a t )  
 {  
 	 i f ( ! s t r c m p ( f o r m a t ,   " D 1 " ) )  
 	 {  
 	 	 w c h a r _ t   * s   =   ( w c h a r _ t * ) m a l l o c ( ( n a m e . l e n g t h ( )   +   4   +   u r l . l e n g t h ( ) )   *   s i z e o f ( w c h a r _ t ) ) ;  
 	 	 w c s c p y ( s ,   n a m e . c _ s t r ( ) ) ;  
 	 	 w c s c a t ( s ,   L " \ u 0 A 0 D " ) ;  
 	 	 w c s c a t ( s ,   u r l . c _ s t r ( ) ) ;  
 	 	 w c s c a t ( s ,   L " \ u 0 A 0 D " ) ;  
 	 	 r e t u r n   ( u i n t 8 _ t * ) s ;  
 	 }  
 	 e l s e   i f ( ! s t r c m p ( f o r m a t ,   " D 2 " ) )  
 	 {  
 	 	 s i z e _ t   l   =   n a m e . l e n g t h ( )   *   s i z e o f ( w c h a r _ t ) ;  
 	 	 c h a r   * s   =   ( c h a r * ) m a l l o c ( l   +   ( 3   +   u r l . l e n g t h ( ) )   *   s i z e o f ( w c h a r _ t ) ) ;  
 	 	 w c s c p y ( ( w c h a r _ t * ) s ,   n a m e . c _ s t r ( ) ) ;  
 	 	 s [ l ]   =   1 1 ;  
 	 	 i f ( ! w c s n c m p ( u r l . c _ s t r ( ) ,   t i n y u r l ,   1 9 ) )  
 	 	 {  
 	 	 	 s [ l   +   1 ]   =   1 ;  
 	 	 	 s t r c a t ( s ,   0 / * u r l . s u b s t r ( 1 9 )   t o   s t r i n g   c _ s t r * / ) ;  
 	 	 	 s [ l   +   1 0 ]   =   1 1 ;  
 	 	 }  
 	 	 e l s e  
 	 	 {  
 	 	 	 s [ l   +   1 ]   =   0 ;  
 	 	 	 w c s c a t ( ( w c h a r _ t * ) s ,   u r l . c _ s t r ( ) ) ;  
 	 	 	 s [ l   +   1   +   u r l . l e n g t h ( )   *   s i z e o f ( w c h a r _ t ) ]   =   1 1 ;  
 	 	 }  
 	 	 l   =   s i z e o f ( s ) ;  
 	 	 c h a r   * t   =   ( c h a r * ) m a l l o c ( l ) ;  
 	 	 m e m c p y ( t ,   s ,   l ) ;  
 	 	 r e t u r n   ( b y t e * ) t ;  
 	 }  
 	 e l s e   i f   ( ! s t r c m p ( f o r m a t ,   " L 1 " ) )  
 	 {  
 	 	 U E r r o r C o d e   e r r   =   U _ Z E R O _ E R R O R ;  
 	 	 U C o n v e r t e r   * c o n v   =   u c n v _ o p e n ( " u t f - 8 " ,   & e r r ) ;  
 	 	 i f   ( ! U _ S U C C E S S ( e r r ) )  
 	 	 {  
 	 	 	 l a s t _ e x c e p t i o n   =   e r r   |   u n i c o d e _ e r r o r ;  
 	 	 	 r e t u r n   0 ;  
 	 	 }  
 	 	 _ _ _ _ _ P L Z _ C O M P L E T E _ T H I S _ I N _ T H E _ F U T U R E _ _ _ _ _  
 	 	 / / e n c o d e   u t f 8   f o r   n a m e   t o   b f r ;  
 	 	 / / i f   ( ! w c s n c m p ( u r l . c _ s t r ( ) ,   t i n y u r l ,   1 9 ) )  
 	 	 / / {  
 	 	 / / 	 w r i t e   1 1   t o   b f r ;  
 	 	 / / 	 w r i t e   b 6 4   d e c o d e   u r l . s u b s t r ( 1 9 )   t o   b f r ;  
 	 	 / / }  
 	 	 / / e l s e  
 	 	 / / {  
 	 	 / / 	 w r i t e   8   t o   b f r ;  
 	 	 / / 	 w r i t e   u t f 8   o f   u r l   t o   b f r ;  
 	 	 / / 	 w r i t e   1 1   t o   b f r ;  
 	 	 / / }  
 	 	 u c n v _ c l o s e ( c o n v ) ;  
 	 }  
 	 r e t u r n   0 ;  
 }  
  
 l i b c w l c p p : : w l : : w l ( )  
 {  
 	 i t e m s   =   0 ;  
 }  
  
 l i b c w l c p p : : w l : : w l ( i t e m   * * i t e m s )  
 {  
 	 t h i s - > i t e m s   =   i t e m s ;  
 }  
  
 b o o l   l i b c w l c p p : : w l : : o p e r a t o r = = ( w l   * w l )  
 {  
 	 r e t u r n   a r r e q u ( ( u i n t 8 _ t * ) & i t e m s [ 0 ] ,   ( u i n t 8 _ t * ) & ( w l - > i t e m s [ 0 ] ) ) ;  
 }  
  
 b o o l   l i b c w l c p p : : w l : : o p e r a t o r ! = ( w l   * w l )  
 {  
 	 r e t u r n   ! a r r e q u ( ( b y t e * ) & i t e m s [ 0 ] ,   ( b y t e * ) & ( w l - > i t e m s [ 0 ] ) ) ;  
 }  
  
 l i b c w l c p p : : w l   l i b c w l c p p : : w l : : o p e r a t o r & ( w l   * w l )  
 {  
 	 v e c t o r < i t e m * >   * i   =   n e w   v e c t o r < i t e m * > ( ) ;  
 	 f o r   ( i t e m   * * p   =   i t e m s ;   * p ;   + + p )  
 	 {  
 	 	 i - > p u s h _ b a c k ( * p ) ;  
 	 }  
 	 i - > p u s h _ b a c k ( 0 ) ;  
 	 r e t u r n   & ( * i ) [ 0 ] ;  
 }  
  
 u l o n g   l i b c w l c p p : : w l : : l e n g t h ( )  
 {  
 	 / / w e   c a n   d o   t h i s   b e c a u s e   w h i l e   i t e m s   h a v e   v a r i a b l e  
 	 / / s i z e   p t r s   a r e   8   b y t e s   o n   A M D 6 4 / x 8 6 _ 6 4   a n d   4   o n   x 8 6  
 	 r e t u r n   s i z e o f ( i t e m s )   /   s i z e o f ( i t e m * )   -   1 ;  
 }  
  
 u l o n g   l i b c w l c p p : : w l : : h l e n ( )  
 {  
 	 u l o n g   i   =   l e n g t h ( )   *   s i z e o f ( i t e m ) ;  
 	 f o r   ( u l o n g   j   =   0 ;   j   <   l e n g t h ( ) ;   j + + )  
 	 {  
 	 	 i t e m   * k   =   i t e m s [ j ] ;  
 	 	 i   + =   ( k - > n a m e . l e n g t h ( )   +   k - > u r l . l e n g t h ( ) )   *   w c l e n   +   2 ;  
 	 }  
 	 i   + =   s i z e o f ( i t e m s ) ;  
 	 r e t u r n   i ;  
 }  
  
 b o o l   l i b c w l c p p : : a r r e q u ( b y t e   * a r r 1 ,   b y t e   * a r r 2 )  
 {  
 	 s i z e _ t   s o   =   s i z e o f ( a r r 1 ) ;  
 	 s i z e _ t   s t   =   s i z e o f ( a r r 2 ) ;  
 	 i f   ( s o   ! =   s t )  
 	 {  
 	 	 r e t u r n   0 ;  
 	 }  
 	 f o r   ( s i z e _ t   i   =   0 ;   i   <   s o ;   i + + )  
 	 {  
 	 	 i f   ( a r r 1 [ i ]   ! =   a r r 2 [ i ] )  
 	 	 {  
 	 	 	 r e t u r n   0 ;  
 	 	 }  
 	 }  
 	 r e t u r n   1 ;  
 }  
  
 w l   * l i b c w l c p p : : i o : : l o a d _ c w l d ( c h a r   * f i l e )  
 {  
 	 F I L E   * f   =   f o p e n ( f i l e ,   " r " ) ;  
 	 l o n g   b   =   f t e l l ( f ) ;  
 	 f s e e k ( f ,   0 ,   S E E K _ E N D ) ;  
 	 l o n g   e   =   f t e l l ( f ) ;  
 	 f s e e k ( f ,   0 ,   S E E K _ S E T ) ;  
 	 l o n g   l   =   e   -   b   -   1 0 ;  
 	 u i n t 8 _ t   h [ 8 ] ;  
 	 f r e a d ( h ,   1 ,   8 ,   f ) ;  
 	 u i n t 8 _ t   v [ 2 ] ;  
 	 f r e a d ( v ,   1 ,   2 ,   f ) ;  
 	 u i n t 8 _ t   m a j o r   =   v [ 0 ] ;  
 	 u i n t 8 _ t   m i n o r   =   v [ 1 ] ;  
 	 u i n t 8 _ t   * c   =   ( u i n t 8 _ t * ) m a l l o c ( l ) ;  
 	 f r e a d ( c ,   1 ,   l ,   f ) ;  
 	 l i b d e f l a t e _ d e c o m p r e s s o r   * d   =   l i b d e f l a t e _ a l l o c _ d e c o m p r e s s o r ( ) ;  
 	 s i z e _ t   u l   =   0 ;  
 	 s i z e _ t   u b f r l e n   =   l   *   1 0 ;  
 	 u i n t 8 _ t   * u b f r   =   ( u i n t 8 _ t * ) m a l l o c ( u b f r l e n ) ;  
 	 l i b d e f l a t e _ r e s u l t   r e s   =   l i b d e f l a t e _ d e f l a t e _ d e c o m p r e s s ( d ,   c ,   l ,   u b f r ,   u b f r l e n ,   & u l ) ;  
 	 l i b d e f l a t e _ f r e e _ d e c o m p r e s s o r ( d ) ;  
 	 f r e e ( c ) ;  
 	 i f   ( r e s )  
 	 {  
 	 	 f r e e ( u b f r ) ;  
 	 	 l a s t _ e x c e p t i o n   =   d e f l a t e _ e r r o r   |   r e s ;  
 	 	 r e t u r n   0 ;  
 	 }  
 	 u i n t 8 _ t   * u   =   ( u i n t 8 _ t * ) m a l l o c ( u l ) ;  
 	 m e m c p y ( u ,   u b f r ,   u l ) ;  
 	 f r e e ( u b f r ) ;  
 	 f c l o s e ( f ) ;  
 	 i f   ( m a j o r   ! =   4 )  
 	 {  
 	 	 l a s t _ e x c e p t i o n   =   0 x 2 0   |   1 ;  
 	 	 r e t u r n   0 ;  
 	 }  
 	 e l s e   i f   ( m i n o r   >   2 )  
 	 {  
 	 	 l a s t _ e x c e p t i o n   =   0 x 2 0   |   2 ;  
 	 	 r e t u r n   0 ;  
 	 }  
 	 e l s e   i f   ( m i n o r   = =   1 )  
 	 {  
 	 	 v e c t o r < i t e m * >   i t e m s ;  
 	 	 w c h a r _ t   * s   =   ( w c h a r _ t * ) m a l l o c ( u l ) ;  
 	 	 u i n t 8 _ t   t m p 1 ;  
 	 	 u i n t 8 _ t   t m p 2 ;  
 	 	 w c h a r _ t   * n ;  
 	 	 s i z e _ t   i ;  
 	 	 s i z e _ t   j ;  
 	 	 w h i l e   ( i   <   u l )  
 	 	 {  
 	 	 	 i f   ( ( t m p 1   =   u [ i + + ] )   = =   1 0   & &   ( t m p 2   =   u [ i + + ] )   = =   1 3 )  
 	 	 	 {  
 	 	 	 	 i f   ( n )  
 	 	 	 	 {  
 	 	 	 	 	 w c h a r _ t   * u r l   =   ( w c h a r _ t * ) m a l l o c ( w c s l e n ( s )   *   s i z e o f ( w c h a r _ t ) ) ;  
 	 	 	 	 	 w c s c p y ( u r l ,   s ) ;  
 	 	 	 	 	 m e m s e t ( s ,   0 ,   u l ) ;  
 	 	 	 	 	 j   =   0 ;  
 	 	 	 	 	 i t e m s . p u s h _ b a c k ( n e w   i t e m ( n ,   u r l ) ) ;  
 	 	 	 	 	 n   =   0 ;  
 	 	 	 	 }  
 	 	 	 	 e l s e  
 	 	 	 	 {  
 	 	 	 	 	 n   =   ( w c h a r _ t * ) m a l l o c ( w c s l e n ( s )   *   s i z e o f ( w c h a r _ t ) ) ;  
 	 	 	 	 	 w c s c p y ( n ,   s ) ;  
 	 	 	 	 	 m e m s e t ( s ,   0 ,   u l ) ;  
 	 	 	 	 	 j   =   0 ;  
 	 	 	 	 }  
 	 	 	 }  
 	 	 	 e l s e  
 	 	 	 {  
 	 	 	 	 u i n t 8 _ t   * m b   =   ( u i n t 8 _ t * ) m a l l o c ( 2 ) ;  
 	 	 	 	 m b [ 0 ]   =   t m p 1 ;  
 	 	 	 	 m b [ 1 ]   =   t m p 2 ;  
 	 	 	 	 w c h a r _ t   * w c   =   ( w c h a r _ t * ) m a l l o c ( s i z e o f ( w c h a r _ t ) ) ;  
 	 	 	 	 m b t o w c ( w c ,   ( c o n s t   c h a r * ) m b ,   2 ) ;  
 	 	 	 	 s [ j + + ]   =   * w c ;  
 	 	 	 	 f r e e ( m b ) ;  
 	 	 	 	 f r e e ( w c ) ;  
 	 	 	 }  
 	 	 }  
 	 	 f r e e ( s ) ;  
 	 	 f r e e ( u ) ;  
 	 	 s i z e _ t   i l   =   i t e m s . s i z e ( )   *   s i z e o f ( i t e m s [ 0 ] ) ;  
 	 	 i t e m   * * i t m s   =   ( i t e m * * ) m a l l o c ( i l ) ;  
 	 	 m e m c p y ( i t m s ,   i t e m s [ 0 ] ,   i l ) ;  
 	 	 i f   ( n )   / / t h i s   b t w   m e a n s   a   b r o k e n   c w l d   b u t   l e t s   b e   s a f e  
 	 	 {  
 	 	 	 f r e e ( n ) ;  
 	 	 }  
 	 	 r e t u r n   n e w   w l ( i t m s ) ;  
 	 }  
 	 e l s e  
 	 {  
 	 	 v e c t o r < i t e m * >   i t e m s ;  
 	 	 w c h a r _ t   * s   =   ( w c h a r _ t * ) m a l l o c ( u l ) ;  
 	 	 w c h a r _ t   * n ;  
 	 	 u i n t 8 _ t   i ;  
 	 	 s i z e _ t   u i ;  
 	 	 s i z e _ t   s i ;  
 	 	 w h i l e   ( u i   <   u l )  
 	 	 {  
 	 	 	 i f   ( ( i   =   u [ u i + + ] )   = =   1 1 )  
 	 	 	 {  
 	 	 	 	 i f   ( n )  
 	 	 	 	 {  
 	 	 	 	 	 w c h a r _ t   * u r l   =   ( w c h a r _ t * ) m a l l o c ( w c s l e n ( s )   *   s i z e o f ( w c h a r _ t ) ) ;  
 	 	 	 	 	 w c s c p y ( u r l ,   s ) ;  
 	 	 	 	 	 m e m s e t ( s ,   0 ,   u l ) ;  
 	 	 	 	 	 s i   =   0 ;  
 	 	 	 	 	 i t e m s . p u s h _ b a c k ( n e w   i t e m ( n ,   u r l ) ) ;  
 	 	 	 	 	 n   =   0 ;  
 	 	 	 	 }  
 	 	 	 	 e l s e  
 	 	 	 	 {  
 	 	 	 	 	 n   =   ( w c h a r _ t * ) m a l l o c ( w c s l e n ( s )   *   s i z e o f ( w c h a r _ t ) ) ;  
 	 	 	 	 	 w c s c p y ( n ,   s ) ;  
 	 	 	 	 	 m e m s e t ( s ,   0 ,   u l ) ;  
 	 	 	 	 	 i f   ( u [ u i + + ] )  
 	 	 	 	 	 {  
 	 	 	 	 	 	 w c s c p y ( s ,   L " h t t p : / / t i n y u r l . c o m / " ) ;  
 	 	 	 	 	 	 s i   =   1 9 ;  
 	 	 	 	 	 }  
 	 	 	 	 	 e l s e  
 	 	 	 	 	 {  
 	 	 	 	 	 	 s i   =   0 ;  
 	 	 	 	 	 }  
 	 	 	 	 }  
 	 	 	 }  
 	 	 	 e l s e  
 	 	 	 {  
 	 	 	 	 u i n t 8 _ t   * m b   =   ( u i n t 8 _ t * ) m a l l o c ( 2 ) ;  
 	 	 	 	 m b [ 0 ]   =   i ;  
 	 	 	 	 m b [ 1 ]   =   u [ u i + + ] ;  
 	 	 	 	 w c h a r _ t   * w c   =   ( w c h a r _ t * ) m a l l o c ( s i z e o f ( w c h a r _ t ) ) ;  
 	 	 	 	 m b t o w c ( w c ,   ( c o n s t   c h a r * ) m b ,   2 ) ;  
 	 	 	 	 s [ s i + + ]   =   * w c ;  
 	 	 	 	 f r e e ( m b ) ;  
 	 	 	 	 f r e e ( w c ) ;  
 	 	 	 }  
 	 	 }  
 	 	 f r e e ( s ) ;  
 	 	 f r e e ( u ) ;  
 	 	 s i z e _ t   i l   =   i t e m s . s i z e ( )   *   s i z e o f ( i t e m s [ 0 ] ) ;   / / t h e   e l e m e n t s   a r e   p o i n t e r s   s o   a l l   e l e m e n t s   h a v e   t h e   s a m e   s i z e  
 	 	 i t e m   * * i t m s   =   ( i t e m * * ) m a l l o c ( i l ) ;  
 	 	 m e m c p y ( i t m s ,   i t e m s [ 0 ] ,   i l ) ;  
 	 	 i f   ( n )   / / t h i s   b t w   m e a n s   a   b r o k e n   c w l d   b u t   l e t s   b e   s a f e  
 	 	 {  
 	 	 	 f r e e ( n ) ;  
 	 	 }  
 	 	 r e t u r n   n e w   w l ( i t m s ) ;  
 	 }  
 }  
 