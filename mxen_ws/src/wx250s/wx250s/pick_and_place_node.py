import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient


from wx250s_interface.action import CartesianPTP
from wx250s_interface.service import PickPlace

from xarmclient import XArm

class PickAndPlaceNode(Node):
    def __init__(self):
        super().__init__("pick_and_place_node")

        ### Robot Init ###
        self.xarm = XArm()
        #######################

        ### Service Server ###
        self.service = self.create_service(PickPlace, "pick_and_place", self.service_callback)
        #####################################################################################

        ### Action Client ###
        self.action_client = ActionClient(self, CartesianPTP, 'set_cartesian_ptp')
        ############################################################################

    ### Service Execution ###
    def service_callback(self, request, response):
        xpick = request[0]
        ypick = request[1]
        xplace = request[2]
        yplace = request[3]
        pick_pos = [xpick, ypick, 10]

        self.action_callback()
        return response
    #######################################################

    ### Action Client Callback ###
    def action_callback(self, goal_request):
        goal_to_send = CartesianPTP.Goal()
        goal_to_send.goal_pos = goal_request
        self.action_client.send_goal_async(goal_to_send)


def main(args=None):

    rclpy.init(args=args)

    node = PickAndPlaceNode()
    rclpy.spin(node)
    node.destroy_node()

    rclpy.shutdown()

    return 0

if __name__ == '__main__':
    main()