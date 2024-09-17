/**
3. Aufgabe
FÜge hier die Abhängigkeiten ein.

Anfang Aufgabe 3
*/


/**
Ende Aufgabe 3
*/

using namespace std::chrono_literals;

class GoalPublisherNode : public rclcpp::Node
{
public:
    GoalPublisherNode()
    : Node("goal_publisher_node")
    {
        /**
        4. Aufgabe
        Hier definieren wir unsere Publisher und Subscriber
        
        Anfang Aufgabe 4 (schon erledigt für euch)
        */

        // Definiere hier den Goal Publisher, ersetze NULL mit der richtigen Definition
        goal_pub_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("/goal_pose", 10);

        // Odometry Subscriber
        odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "/odom", 10, std::bind(&GoalPublisherNode::odom_callback, this, 	std::placeholders::_1));

        /**
        Ende Aufgabe 4
        */

        // Methode um Ziele zu laden
        load_goal_points();

        // Das erste Ziel publishen
        publish_next_goal();
    }

private:

    void load_goal_points()
    {
        // Liste der Ziele
        std::vector<std::vector<double>> goal_points = {
            {1.0, 0.0, 0.0, 1.0},
            {2.0, 0.0, 0.0, 1.0},
            {3.0, 0.0, 0.0, 1.0},
            {1.0, 1.0, 0.0, 1.0},
            {2.0, 1.0, 0.0, 1.0},
            {3.0, 1.0, 0.0, 1.0},
            {1.0, 0.0, -1.0, 1.0}
        };

        for (const auto &point : goal_points) {
            if (point.size() == 4) {
                geometry_msgs::msg::PoseStamped goal;
                goal.header.frame_id = "map";
                goal.pose.position.x = point[0];
                goal.pose.position.y = point[1];
                goal.pose.position.z = point[2];
                goal.pose.orientation.w = point[3];
                goals_.push_back(goal);
            } else {
                RCLCPP_ERROR(this->get_logger(), "Invalid goal point size: %zu", point.size());
            }
        }
    }

    void publish_next_goal()
    {
        if (goal_index_ >= goals_.size()) {
            RCLCPP_INFO(this->get_logger(), "All goals have been reached.");
            finished_ = true;
            return;
        }

        auto goal = goals_[goal_index_];
        goal.header.stamp = this->now();
        goal_pub_->publish(goal);
        RCLCPP_INFO(this->get_logger(), "Published goal %zu: [%.2f, %.2f, %.2f, %.2f]", goal_index_,
                    goal.pose.position.x, goal.pose.position.y, goal.pose.position.z, goal.pose.orientation.w);

        current_goal_ = goal;
    }

    void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
    {
         /**
        6. Aufgabe
        Rechne die Distanz zwischen Ziel und Roboter aus.
        
        Anfang Aufgabe 6
        */

        double current_x = NULL;
        double current_y = NULL;
        double goal_x = NULL;
        double goal_y = NULL;

        // Berechne hier die Distanz wie in der Folie beschrieben
        double distance = NULL;

        /**
        Ende Aufgabe 6
        */
    
        
        goal_pub_->publish(current_goal_);
        

        if (distance < goal_tolerance_) {
            if(!finished_)
                {
                    RCLCPP_INFO(this->get_logger(), "Reached goal %zu", goal_index_);
                }
            goal_index_++;
            publish_next_goal();
        }
    }

    rclcpp::Publisher<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr initial_pose_pub_;
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr goal_pub_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
    std::vector<geometry_msgs::msg::PoseStamped> goals_;
    geometry_msgs::msg::PoseStamped current_goal_;
    bool finished_ = false;
    size_t goal_index_ = 0;
    const double goal_tolerance_ = 0.3;  // Toleranz in Meter, in der ein Ziel als Erreicht gilt
};

int main(int argc, char **argv)
{
    /**
        5. Aufgabe
        Implementiere die Main-Funktion.
        
        Anfang Aufgabe 5
        */


        /**
        Ende Aufgabe 5
        */
    
}
