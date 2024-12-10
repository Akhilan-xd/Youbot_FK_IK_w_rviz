import xml.etree.ElementTree as ET
import math

# Function to calculate DH parameters from URDF
def extract_dh_parameters(file_path):
    def parse_origin(origin_element):
        """Parse the origin element for translation and rotation."""
        if origin_element is None:
            return [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]
        xyz = [float(x) for x in origin_element.attrib.get('xyz', '0 0 0').split()]
        rpy = [float(r) for r in origin_element.attrib.get('rpy', '0 0 0').split()]
        return xyz, rpy

    def dh_parameters_from_transform(xyz, rpy):
        """Convert translation and rotation to DH parameters."""
        d = xyz[2]  # Distance along z-axis
        a = xyz[0]  # Distance along x-axis
        alpha = rpy[0]  # Twist angle
        theta = rpy[2]  # Rotation angle
        return a, alpha, d, theta

    # Parse the URDF file
    tree = ET.parse(file_path)
    root = tree.getroot()

    dh_parameters = []

    # Loop through all joints
    for joint in root.findall('joint'):
        name = joint.attrib.get('name')
        joint_type = joint.attrib.get('type')
        origin = joint.find('origin')

        # Extract xyz and rpy
        xyz, rpy = parse_origin(origin)

        # Convert to DH parameters
        a, alpha, d, theta = dh_parameters_from_transform(xyz, rpy)
        dh_parameters.append({
            'joint': name,
            'type': joint_type,
            'a': a,
            'alpha': alpha,
            'd': d,
            'theta': theta
        })

    return dh_parameters


# Main function
if __name__ == "__main__":
    urdf_file = "/home/akhilan/Downloads/RM_TA_WS_24/24_25 ASSGN_04_Feedback/robot-manipualtion-ws-2425-Akhilan-xd/urdf/youbot.urdf"  # Replace with your URDF file path
    dh_params = extract_dh_parameters(urdf_file)

    # Print DH parameters
    print("DH Parameters:")
    for param in dh_params:
        print(f"Joint: {param['joint']}")
        print(f"  Type: {param['type']}")
        print(f"  a: {param['a']:.4f}, alpha: {math.degrees(param['alpha']):.2f}°")
        print(f"  d: {param['d']:.4f}, theta: {math.degrees(param['theta']):.2f}°\n")
