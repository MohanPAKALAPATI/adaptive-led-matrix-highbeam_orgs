# Test cases for vehicleDetect.py
import unittest
from unittest.mock import MagicMock
import numpy as np

# We need to import the functions to be tested.
# Since the functions are in a script, we can import the script as a module.
import vehicleDetect

class TestVehicleDetect(unittest.TestCase):
    def setUp(self):
        """Set up for the tests."""
        self.mock_serial = MagicMock()
        # Create a dummy frame with a width of 1000
        self.mock_frame = np.zeros((480, 1000, 3), dtype=np.uint8)

    def test_drawCurtainSingle_pos0(self):
        """Test drawCurtainSingle for position 0."""
        # col1 = 1000 * 0.1 - 20 = 80
        vehicleDetect.drawCurtainSingle(self.mock_frame, 50, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'xy0')

    def test_drawCurtainSingle_pos1(self):
        """Test drawCurtainSingle for position 1."""
        # col1 = 80, col2 = 200
        vehicleDetect.drawCurtainSingle(self.mock_frame, 100, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'xy1')

    def test_drawCurtainSingle_pos2(self):
        """Test drawCurtainSingle for position 2."""
        # col2 = 200, col3 = 300
        vehicleDetect.drawCurtainSingle(self.mock_frame, 250, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'xy2')

    def test_drawCurtainSingle_pos3(self):
        """Test drawCurtainSingle for position 3."""
        # col3 = 300, col4 = 400
        vehicleDetect.drawCurtainSingle(self.mock_frame, 350, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'xy3')

    def test_drawCurtainSingle_pos4(self):
        """Test drawCurtainSingle for position 4."""
        # col4 = 400, col5 = 500
        vehicleDetect.drawCurtainSingle(self.mock_frame, 450, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'xy4')

    def test_drawCurtainSingle_pos5(self):
        """Test drawCurtainSingle for position 5."""
        # col5 = 500, col6 = 600
        vehicleDetect.drawCurtainSingle(self.mock_frame, 550, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'xy5')

    def test_drawCurtainSingle_pos6(self):
        """Test drawCurtainSingle for position 6."""
        # col6 = 600, col7 = 700
        vehicleDetect.drawCurtainSingle(self.mock_frame, 650, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'xy6')

    def test_drawCurtainSingle_pos7(self):
        """Test drawCurtainSingle for position 7."""
        # col7 = 700, col8 = 800
        vehicleDetect.drawCurtainSingle(self.mock_frame, 750, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'xy7')

    def test_drawCurtainSingle_pos8(self):
        """Test drawCurtainSingle for position 8."""
        # col8 = 800, col9 = 900
        vehicleDetect.drawCurtainSingle(self.mock_frame, 850, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'xy8')

    def test_drawCurtainSingle_pos9(self):
        """Test drawCurtainSingle for position 9."""
        # col9 = 900
        vehicleDetect.drawCurtainSingle(self.mock_frame, 950, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'xy9')

    def test_drawCurtainDouble_1_5(self):
        """Test drawCurtainDouble for positions 1 and 5."""
        # inpX1 = 100 (pos 1), inpX2 = 550 (pos 5)
        vehicleDetect.drawCurtainDouble(self.mock_frame, 100, 550, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'x15')

    def test_drawCurtainDouble_8_2(self):
        """Test drawCurtainDouble for positions 8 and 2."""
        # inpX1 = 850 (pos 8), inpX2 = 250 (pos 2)
        vehicleDetect.drawCurtainDouble(self.mock_frame, 850, 250, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'x82')

    def test_drawCurtainDouble_3_out_of_bounds(self):
        """Test drawCurtainDouble for position 3 and an out-of-bounds position."""
        # inpX1 = 350 (pos 3), inpX2 = 950 (pos 0)
        vehicleDetect.drawCurtainDouble(self.mock_frame, 350, 950, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'x30')

    def test_ledOnOff_on(self):
        """Test ledOnOff for state 1 (no vehicles)."""
        vehicleDetect.ledOnOff(1, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'xy0')

    def test_ledOnOff_off(self):
        """Test ledOnOff for state 0 (more than 2 vehicles)."""
        vehicleDetect.ledOnOff(0, self.mock_serial)
        self.mock_serial.write.assert_called_with(b'xy9')
