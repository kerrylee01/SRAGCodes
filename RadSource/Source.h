#ifdef __cplusplus
  extern "C" {
#endif

enum error { OK, 
	     SOURCE_ENV_NOT_FOUND, 
	     INVALID_SPECTRAL_TYPE,
             SOURCE_TYPE_NOT_SPECIFIED};

void setup_source_(double &origin_x, double &origin_y, double &origin_z,
		   double &x_width, double &y_width, double &radius,
		   double &z_shift, int &ionid, int &spectrum_type, int &err,
		   char *src_type, int &string_length);

void sample_source_(double *randoms, int& num_randoms, double &xxx, double &yyy, double &zzz,
             double &uuu, double &vvv, double &www,
             double &energy, double &weight, double &am,
             int &ionID, int &charge, int &nucleon_num);

#ifdef __cplusplus
    }
#endif
