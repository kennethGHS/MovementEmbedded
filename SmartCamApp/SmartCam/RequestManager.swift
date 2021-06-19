//
//  RequestManager.swift
//  SmartCam
//
//  Created by Jasson Rodríguez Méndez on 18/6/21.
//

import Foundation
import SwiftUI
import Combine

class RequestManager : ObservableObject {
    @Published var detectionList = ["No motion detected"]
    @Published var currentImage = UIImage(named: "Placeholder")
    
    init () {
        guard let url = URL(string: "http://192.168.100.62:8000/api/images") else { return }
        URLSession.shared.dataTask(with: url) { data, _, _ in
            guard let receivedData = data else { return }
            let detectionList = try! JSONDecoder().decode([String].self, from: receivedData)
            DispatchQueue.main.async {
                self.detectionList = detectionList
            }
        }.resume()
    }
    
    func getImage(name: String) {
        guard let url = URL(string: "http://192.168.100.62:8000/api/" + name) else { return }
        URLSession.shared.dataTask(with: url) { data, _, _ in
            guard let imageData = data else { return }
            let image = UIImage(data: imageData)
            DispatchQueue.main.async {
                self.currentImage = image
            }
        }.resume()
    }
}
