/**
 * @file tracking.hpp
 * @author Lowell Lobo
 * @author Mayank Deshpande
 * @author Kautilya Chappidi
 * @brief Class Definition for the TrackingClass
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 */

#ifndef TRACKING_HPP
#define TRACKING_HPP

#include <map>
#include <bits/stdc++.h>
#include <algorithm>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

#include "detection.hpp"

/**
 * @class TrackingClass
 * @brief A class for Tracking Subjects on the Frame.
 *
 * This class takes the Image Frames as an inout and will
 * track any Human subjects as and when they are detected in the frame
 */
class TrackingClass {
 public:
 /**
  * @brief Variables x, y and z that hold the values of distance between the
  * Car reference frame and Camera reference frame
  */
  double xOffset, yOffset, zOffset;
  /**
   * @brief Variables horizontalFOI, verticalFOI that hold the values for Camera 
   * Field of View
   */
  double horizontalFOI, verticalFOI;
  /**
   * @brief Vector that holds the position of all obstacles found in image
   * frame after assigning unique IDs
   *
   */
  std::map<int, cv::Rect> obstacleMapVector;
  /**
   * @brief Object of class DetectionClass (part-of relation), used to access
   * the video stream and get detection of obstacles.
   *
   */
  DetectionClass image;
  /**
   * @brief Constructor for TrackingClass.
   */
  TrackingClass(const std::string& detectModelPath,
                             const std::string& detectConfigPath);

  /**
   * @brief Destructor for TrackingClass.
   */
  ~TrackingClass();

  /**
   * @brief Finds the depth of an object.
   * The function will be called by distFromCamera() to get the
   * @param id The ID of the bounding box whose depth needs to be found
   * @return Depth value.
   */
  double findDepth(int id);

  /**
   * @brief Assigns IDs to objects.
   * The function is called after face detection.
   * The function assigns unique IDs in the first iteration of face detection.
   * In subsequent iterations, the function will compare the the current
   * obstacleMapVector with the new face detection and assign IDs to the new
   * bounding box based on minimum Euclidean Distance
   * 
   * @param detections 
   * @return std::map<int, cv::Rect> A map containing object IDs and descriptions.
   */
  std::map<int, cv::Rect> assignIDAndTrack(
      std::vector<cv::Rect>& detections);

/**
 * @brief Calculates the distance of an object from the camera.
 * The function computes the
 * x and y distance and calls findDepth() to get the z distance.
 *
 * @param frameWidth 
 * @param frameHeight 
 * @return std::map<int, std::tuple<double, double, double>> A map containing the ID and a tuple containing x distance, y
   * distance, and z distance of the corresponding ID. 
 */
  std::map<int, std::tuple<double, double, double>>
  distFromCamera(int frameWidth, int frameHeight);

  /**
   * @brief Calculates the distance of an object from a car.
   * The function takes in distance from camera frame and performs a
   * transformation to get the distance from robot frame.
   * @param input Input map with tuple containing object information.
   * @return A map with tuple containing x distance, y distance, and z distance from
   * robot reference frame.
   */
  std::map<int, std::tuple<double, double, double>> distFromCar(
      const std::map<int, std::tuple<double, double, double>>& input);

};

#endif