#include <cmath>
#include <iostream>

#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

double hit_sphere(const point3& center, double radius, const ray& r){
  vec3 oc = center - r.origin();
  auto a = dot(r.direction(), r.direction());
  auto h = dot(r.direction(), oc);
  auto c = dot(oc, oc) - radius*radius;
  auto modified_d = h*h - a*c;
  if (modified_d < 0){
    return -1.0;
  } else {
    return (h - std::sqrt(modified_d)) / a;
  }
  return modified_d >= 0;
}

color ray_color(const ray& r){
  // Ray coloring for sphere
  auto t = hit_sphere(point3(0,0,-1), 0.5, r);
  if(t > 0.0){
    vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
    return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
  }

  // Gradient
  auto unit_direction = unit_vector(r.direction());
  // Scaling done as unit direction -> [-1,1] and we need a -> [0,1]
  auto a = 0.5*(unit_direction.y() + 1.0);
  return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
}

int main(){
  // Image
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = int(image_width/aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // Camera
  double focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (double(image_width)/image_height);
  auto camera_center = point3(0,0,0);

  auto Vu = vec3(viewport_width, 0, 0);
  auto Vv = vec3(0, -viewport_height, 0);

  auto pixel_delta_u = Vu / image_width;
  auto pixel_delta_v = Vv / image_height;

  auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - Vu/2 -Vv/2;
  auto pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u + pixel_delta_v);

  // Render
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for(int j = 0; j < image_height; j++){
    std::clog << "\rScanlines remaining: " << (image_height-j) << ' ' << std::flush;
    for(int i = 0; i < image_width; i++){
      auto pixel_center = pixel00_loc + (i*pixel_delta_u) + (j * pixel_delta_v);
      auto ray_direction = pixel_center - camera_center;
      ray r(camera_center, ray_direction);

      color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }
  std::clog << "\rDone.                  \n";
}
