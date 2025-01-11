# Skin Lesion Detection and Analysis Using Image Processing

This project implements techniques for detecting and analyzing skin lesions through image processing methods. It focuses on identifying lesion regions using **Connected Components Labeling**, **K-Means Clustering**, and evaluating the results using the **DICE Coefficient**. The implementation also includes **Run Length Encoding (RLC)** for efficient storage of segmented images. The project adheres to modular and readable coding practices, making it well-suited for further enhancements.

---

## Key Features
- **Connected Components Labeling:** Identify and label the largest connected lesion region in segmented images.
- **K-Means Clustering:** Segment lesion regions from original-colored images using pixel intensity clustering.
- **DICE Coefficient:** Evaluate the accuracy of lesion detection against ground truth images.
- **Run Length Encoding (RLC):** Encode binary segmented lesion images for efficient storage and transmission.

---

## Setup Instructions

### 1. Install OpenCV and Set Environment Variables
Follow the steps in this [YouTube tutorial](https://www.youtube.com/watch?v=aMXQshF7zdo) to:
1. Download and install OpenCV.
2. Set environment variables for OpenCV to ensure compatibility with Visual Studio.

### 2. Configure Project Paths
After setting up OpenCV, configure the paths in the Visual Studio project files to ensure the project compiles and runs successfully. Update the include directories and linker settings as needed.

---

## Project Steps

### **Step 1: Connected Components Labeling**
- Analyzed segmented output images to identify all connected components.
- Focused on the largest component (lesion) based on the number of connected pixels.
- Assigned unique labels to each component and visualized the lesion with a label of `1`.

### **Step 2: K-Means Clustering**
- Applied K-Means clustering to the original-colored images.
- Used two centroids for clustering: one for the lesion (darker pixels) and one for non-lesion (lighter pixels).
- Segmented lesions into binary images with lesions marked as `1` and the rest as `0`.

### **Step 3: DICE Coefficient Evaluation**
- Compared the detected lesion regions with ground truth images.
- Calculated the **DICE Coefficient** using the formula:
  \[
  DICE = \frac{2 \cdot |TP|}{2 \cdot |TP| + |FP|}
  \]
- True Positive (TP): Pixels correctly identified as lesions.
- False Positive (FP): Pixels incorrectly identified as lesions.

### **Step 4: Run Length Encoding (RLC)**
- Encoded binary segmented lesion images using Run Length Encoding.
- Stored column indices of contiguous pixel blocks representing lesions row-wise.
- Used a **LinkedList** to efficiently store the RLC data.

---

## Project Highlights
- The code is modular, readable, and well-structured for ease of understanding and extension.
- Implements core image processing algorithms without relying on built-in functions (except for image reading).
- Designed to handle both binary and colored image processing efficiently.

---

## Usage Instructions
1. Clone the repository.
2. Set up OpenCV as described above.
3. Configure the Visual Studio project paths.
4. Build and run the project.
5. The Dataset zip contains "Segmented images", "Grouth Truths" and "Original Images", Please set the paths in the code files accordingly. The dataset has been uploaded using LFS

Feel free to explore the implementation and contribute to enhance its features!
