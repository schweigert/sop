int n = 1;

Semaphore sz, sx, sy;

void X() {
 
 n *= 16;
 up(&sz);
}

void Y() {
 down(&sy);
 n /= 7;
}

void Z() {
 down(&sz);
 n += 40;
 up(&sz);
}
